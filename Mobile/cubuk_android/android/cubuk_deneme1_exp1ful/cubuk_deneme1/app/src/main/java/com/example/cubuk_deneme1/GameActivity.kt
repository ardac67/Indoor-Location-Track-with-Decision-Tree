package com.example.cubuk_deneme1

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.graphics.ImageFormat
import android.graphics.SurfaceTexture
import android.hardware.camera2.*
import android.hardware.camera2.params.OutputConfiguration
import android.hardware.camera2.params.SessionConfiguration
import android.media.ImageReader
import android.os.Bundle
import android.os.Handler
import android.os.HandlerThread
import android.util.Log
import android.view.Surface
import android.view.TextureView
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.example.cubuk_deneme1.databinding.ActivityGameBinding
import com.google.zxing.BinaryBitmap
import com.google.zxing.MultiFormatReader
import com.google.zxing.common.HybridBinarizer
import com.google.zxing.PlanarYUVLuminanceSource
import com.example.cubuk_deneme1.utils.StaticGameDatas


class GameActivity : AppCompatActivity() {
    private lateinit var binding: ActivityGameBinding


    private var cameraDevice: CameraDevice? = null
    private lateinit var textureView: TextureView
    private lateinit var imageReader: ImageReader
    private lateinit var captureSession: CameraCaptureSession
    private lateinit var previewRequestBuilder: CaptureRequest.Builder
    private lateinit var handlerThread: HandlerThread
    private lateinit var backgroundHandler: Handler

    external fun sendHitToServer(sock: Int, userId: Int, enemyId: String): Int


    companion object {
        private const val REQUEST_CAMERA_PERMISSION = 1
        private const val CAMERA_ID = "0"

        init {
            System.loadLibrary("cubuk_deneme1")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityGameBinding.inflate(layoutInflater)
        setContentView(binding.root)

        textureView = findViewById(R.id.textureView)
        val pressButton: Button = findViewById(R.id.btnPress)

        if (!allPermissionsGranted()) {
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.CAMERA), REQUEST_CAMERA_PERMISSION)
        } else {
            startBackgroundThread()
            openCamera()
        }


        pressButton.setOnClickListener {
            val currentUser = StaticGameDatas.user;
            if (currentUser != null) {
                Log.d("clicked","User ID: ${currentUser.userId}, Username: ${currentUser.userName}")
                // Use the user data here
            } else {
                Log.d("clicked","No user data available")
            }

            captureStillPicture()
        }
    }

    override fun onBackPressed() {

    }

    fun updateKillDeathView(kills: Int, deaths: Int) {
        // Update the TextViews in the UI with the new kills and deaths
        val killsTextView = findViewById<TextView>(R.id.tvKills)
        val deathsTextView = findViewById<TextView>(R.id.tvDeaths)
        killsTextView.text = "Knockouts: $kills"
        deathsTextView.text = "Pass out: $deaths"
    }

    private fun allPermissionsGranted() = ContextCompat.checkSelfPermission(
        this, Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED

    private fun openCamera() {
        val manager = getSystemService(Context.CAMERA_SERVICE) as CameraManager
        try {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
                return
            }
            manager.openCamera(CAMERA_ID, object : CameraDevice.StateCallback() {
                override fun onOpened(camera: CameraDevice) {
                    cameraDevice = camera
                    startPreview()
                }

                override fun onDisconnected(camera: CameraDevice) {
                    camera.close()
                }

                override fun onError(camera: CameraDevice, error: Int) {
                    camera.close()
                    cameraDevice = null
                }
            }, backgroundHandler)
        } catch (e: CameraAccessException) {
            Toast.makeText(this, "Camera access failed", Toast.LENGTH_LONG).show()
        }
    }

    private fun startPreview() {
        textureView.surfaceTexture?.let { surfaceTexture ->
            surfaceTexture.setDefaultBufferSize(1920, 1080)
            val surface = Surface(surfaceTexture)
            imageReader = ImageReader.newInstance(1920, 1080, ImageFormat.YUV_420_888, 2)
            previewRequestBuilder = cameraDevice!!.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW)
            previewRequestBuilder.addTarget(surface)

            val outputs = listOf(OutputConfiguration(surface), OutputConfiguration(imageReader.surface))
            val sessionStateCallback = object : CameraCaptureSession.StateCallback() {
                override fun onConfigured(session: CameraCaptureSession) {
                    if (cameraDevice == null) return
                    captureSession = session
                    previewRequestBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO)
                    val previewRequest = previewRequestBuilder.build()
                    session.setRepeatingRequest(previewRequest, null, backgroundHandler)
                }

                override fun onConfigureFailed(session: CameraCaptureSession) {
                    Toast.makeText(this@GameActivity, "Failed to configure camera.", Toast.LENGTH_SHORT).show()
                }
            }

            val sessionConfiguration = SessionConfiguration(
                SessionConfiguration.SESSION_REGULAR,
                outputs,
                mainExecutor,
                sessionStateCallback
            )

            cameraDevice?.createCaptureSession(sessionConfiguration)
        }
    }

    private fun captureStillPicture() {
        val captureBuilder = cameraDevice?.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE)?.apply {
            addTarget(imageReader.surface)
            set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO)
        }
        captureSession.capture(captureBuilder!!.build(), object : CameraCaptureSession.CaptureCallback() {
            override fun onCaptureCompleted(session: CameraCaptureSession, request: CaptureRequest, result: TotalCaptureResult) {
                super.onCaptureCompleted(session, request, result)
//                runOnUiThread { Toast.makeText(this@GameActivity, "2", Toast.LENGTH_SHORT).show() }
            }
        }, null)

        imageReader.setOnImageAvailableListener({ reader ->
            reader.acquireNextImage().use { image ->
                val buffer = image.planes[0].buffer
                val data = ByteArray(buffer.remaining())
                buffer.get(data)
                val source = PlanarYUVLuminanceSource(data, image.width, image.height, 0, 0, image.width, image.height, false)
                val bitmap = BinaryBitmap(HybridBinarizer(source))
                try {
                    val result = MultiFormatReader().decode(bitmap)
                    runOnUiThread { Toast.makeText(this, "QR Code detected: ${result.text}", Toast.LENGTH_LONG).show() }
                    sendHitToServer(StaticGameDatas.sock, StaticGameDatas.user.userId, result.text)
                } catch (e: Exception) {
                    runOnUiThread { Toast.makeText(this, "No QR Code detected", Toast.LENGTH_SHORT).show() }
                }
            }
        }, backgroundHandler)
    }


    private fun startBackgroundThread() {
        handlerThread = HandlerThread("CameraBackground").apply {
            start()
        }
        backgroundHandler = Handler(handlerThread.looper)
    }

    private fun stopBackgroundThread() {
        handlerThread.quitSafely()
        try {
            handlerThread.join()
        } catch (e: InterruptedException) {
            e.printStackTrace()
        }
    }

    override fun onResume() {
        super.onResume()
        startBackgroundThread()
        if (textureView.isAvailable) {
            openCamera()
        } else {
            textureView.surfaceTextureListener = surfaceTextureListener
        }
    }

    override fun onPause() {
        closeCamera()
        stopBackgroundThread()
        super.onPause()
    }

    private fun closeCamera() {
        captureSession.close()
        cameraDevice?.close()
        cameraDevice = null
        imageReader.close()
    }

    private val surfaceTextureListener = object : TextureView.SurfaceTextureListener {
        override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
            openCamera()
        }

        override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {
            // Handle size changes if necessary
        }

        override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
            return true
        }

        override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {
            // Update your view if necessary
        }
    }
//    private var cameraDevice: CameraDevice? = null
//    private lateinit var textureView: TextureView
//    private lateinit var imageReader: ImageReader
//    private lateinit var captureSession: CameraCaptureSession
//    private lateinit var previewRequestBuilder: CaptureRequest.Builder
//    private lateinit var handlerThread: HandlerThread
//    private lateinit var backgroundHandler: Handler
//
//    companion object {
//        private const val REQUEST_CAMERA_PERMISSION = 1
//        private const val CAMERA_ID = "0"
//    }
//
//    override fun onCreate(savedInstanceState: Bundle?) {
//        super.onCreate(savedInstanceState)
//        setContentView(R.layout.activity_game)
//
//        textureView = findViewById(R.id.textureView)
//        val pressButton: Button = findViewById(R.id.btnPress)
//
//        if (!allPermissionsGranted()) {
//            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.CAMERA), REQUEST_CAMERA_PERMISSION)
//        } else {
//            startBackgroundThread()
//            openCamera()
//        }
//
//        pressButton.setOnClickListener {
//            captureStillPicture()
//        }
//    }
//
//    private fun allPermissionsGranted() = ContextCompat.checkSelfPermission(
//        this, Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED
//
//    private fun openCamera() {
//        val manager = getSystemService(Context.CAMERA_SERVICE) as CameraManager
//        try {
//            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
//                return
//            }
//            manager.openCamera(CAMERA_ID, object : CameraDevice.StateCallback() {
//                override fun onOpened(camera: CameraDevice) {
//                    cameraDevice = camera
//                    startPreview()
//                }
//
//                override fun onDisconnected(camera: CameraDevice) {
//                    camera.close()
//                }
//
//                override fun onError(camera: CameraDevice, error: Int) {
//                    camera.close()
//                    cameraDevice = null
//                }
//            }, backgroundHandler)
//        } catch (e: CameraAccessException) {
//            Toast.makeText(this, "Camera access failed", Toast.LENGTH_LONG).show()
//        }
//    }
//
//    private fun startPreview() {
//        textureView.surfaceTexture?.let { surfaceTexture ->
//            surfaceTexture.setDefaultBufferSize(1920, 1080)
//            val surface = Surface(surfaceTexture)
//            imageReader = ImageReader.newInstance(1920, 1080, ImageFormat.YUV_420_888, 2)
//            previewRequestBuilder = cameraDevice!!.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW)
//            previewRequestBuilder.addTarget(surface)
//
//            val outputs = listOf(OutputConfiguration(surface), OutputConfiguration(imageReader.surface))
//            val sessionStateCallback = object : CameraCaptureSession.StateCallback() {
//                override fun onConfigured(session: CameraCaptureSession) {
//                    if (cameraDevice == null) return
//                    captureSession = session
//                    previewRequestBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO)
//                    val previewRequest = previewRequestBuilder.build()
//                    session.setRepeatingRequest(previewRequest, null, backgroundHandler)
//                }
//
//                override fun onConfigureFailed(session: CameraCaptureSession) {
//                    Toast.makeText(this@GameActivity, "Failed to configure camera.", Toast.LENGTH_SHORT).show()
//                }
//            }
//
//            val sessionConfiguration = SessionConfiguration(
//                SessionConfiguration.SESSION_REGULAR,
//                outputs,
//                mainExecutor,
//                sessionStateCallback
//            )
//
//            cameraDevice?.createCaptureSession(sessionConfiguration)
//        }
//    }
//
//    private fun captureStillPicture() {
//        val captureBuilder = cameraDevice?.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE)?.apply {
//            addTarget(imageReader.surface)
//            set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO)
//        }
//        captureSession.capture(captureBuilder!!.build(), object : CameraCaptureSession.CaptureCallback() {
//            override fun onCaptureCompleted(session: CameraCaptureSession, request: CaptureRequest, result: TotalCaptureResult) {
//                super.onCaptureCompleted(session, request, result)
////                runOnUiThread { Toast.makeText(this@GameActivity, "2", Toast.LENGTH_SHORT).show() }
//            }
//        }, null)
//
//        imageReader.setOnImageAvailableListener({ reader ->
//            reader.acquireNextImage().use { image ->
//                val buffer = image.planes[0].buffer
//                val data = ByteArray(buffer.remaining())
//                buffer.get(data)
//                val source = PlanarYUVLuminanceSource(data, image.width, image.height, 0, 0, image.width, image.height, false)
//                val bitmap = BinaryBitmap(HybridBinarizer(source))
//                try {
//                    val result = MultiFormatReader().decode(bitmap)
//                    runOnUiThread { Toast.makeText(this, "QR Code detected: ${result.text}", Toast.LENGTH_LONG).show() }
//
//                } catch (e: Exception) {
//                    runOnUiThread { Toast.makeText(this, "No QR Code detected", Toast.LENGTH_SHORT).show() }
//                }
//            }
//        }, backgroundHandler)
//    }
//
//
//    private fun startBackgroundThread() {
//        handlerThread = HandlerThread("CameraBackground").apply {
//            start()
//        }
//        backgroundHandler = Handler(handlerThread.looper)
//    }
//
//    private fun stopBackgroundThread() {
//        handlerThread.quitSafely()
//        try {
//            handlerThread.join()
//        } catch (e: InterruptedException) {
//            e.printStackTrace()
//        }
//    }
//
//    override fun onResume() {
//        super.onResume()
//        startBackgroundThread()
//        if (textureView.isAvailable) {
//            openCamera()
//        } else {
//            textureView.surfaceTextureListener = surfaceTextureListener
//        }
//    }
//
//    override fun onPause() {
//        closeCamera()
//        stopBackgroundThread()
//        super.onPause()
//    }
//
//    private fun closeCamera() {
//        captureSession.close()
//        cameraDevice?.close()
//        cameraDevice = null
//        imageReader.close()
//    }
//
//    private val surfaceTextureListener = object : TextureView.SurfaceTextureListener {
//        override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
//            openCamera()
//        }
//
//        override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {
//            // Handle size changes if necessary
//        }
//
//        override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
//            return true
//        }
//
//        override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {
//            // Update your view if necessary
//        }
//    }
}
