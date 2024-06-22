package com.example.cubuk_deneme1

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.cubuk_deneme1.databinding.ActivityLoginBinding
import com.example.cubuk_deneme1.utils.StaticGameDatas

class LoginActivity : AppCompatActivity() {

    private lateinit var binding: ActivityLoginBinding

    external fun connectToServer(ip: String, port: Int): Int
    external fun disconnectFromServer(sock: Int): Boolean

    var sock: Int = 0

    companion object {
        init {
            System.loadLibrary("cubuk_deneme1")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityLoginBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.buttonLogin.setOnClickListener {
            val ip = binding.editTextIp.text.toString()
            val port = binding.editTextPort.text.toString().toIntOrNull()

            if (ip.isNotEmpty() && port != null) {
                sock = connectToServer(ip, port)
                Log.i("LoginActivity", "Socket: $sock")
//                val sock = 1;
                if (sock != 0) {
                    StaticGameDatas.sock = sock
                    val intent = Intent(this@LoginActivity, MainActivity::class.java)
                    startActivity(intent)
//                    finish()
                    //} else {
//                    Toast.makeText(this, "Could not connect to server", Toast.LENGTH_SHORT).show()
                    //}
                } else {
                    Toast.makeText(this, "Please enter valid IP and Port", Toast.LENGTH_SHORT)
                        .show()
                }
            }
        }

        //external fun connectToServer(ip: String, port: Int): Int

        //companion object {
        //    init {
        //        System.loadLibrary("cubuk_deneme1")
        //    }
        //}
    }

    override fun onDestroy() {
        super.onDestroy()
        disconnectFromServer(sock)
    }
}