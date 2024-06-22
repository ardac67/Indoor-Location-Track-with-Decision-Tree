package com.example.cubuk_deneme1

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.example.cubuk_deneme1.databinding.ActivityMainBinding
import android.widget.EditText
import android.widget.Button
import android.widget.Spinner
import android.widget.ArrayAdapter
import android.widget.Toast
import androidx.core.content.ContextCompat
import android.content.res.ColorStateList
import android.content.Intent
import android.util.Log
import com.example.cubuk_deneme1.utils.StaticGameDatas
import com.example.cubuk_deneme1.utils.User



class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private var sock: Int = 0

//    external fun connectToServer(ip: String, port: Int): Int
    external fun disconnectFromServer(sock: Int): Boolean

    external fun sendToServer(sock: Int, teamId: Boolean, userName: String): Int

    companion object {
        init {
            System.loadLibrary("cubuk_deneme1")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Switch'in durumunu dinleyin ve renkleri güncelleyin
        binding.switchTeam.setOnCheckedChangeListener { _, isChecked ->
            if (isChecked) {
                binding.switchTeam.text = getString(R.string.team_2) // "Team 2" yazısını göster
                binding.mainContainer.setBackgroundColor(ContextCompat.getColor(this, R.color.team2_background))
                binding.switchTeam.trackTintList = ContextCompat.getColorStateList(this, R.color.switch_track_on_team2)
                binding.switchTeam.thumbTintList = ContextCompat.getColorStateList(this, R.color.switch_thumb_on_team2)
            } else {
                binding.switchTeam.text = getString(R.string.team_1) // "Team 1" yazısını göster
                binding.mainContainer.setBackgroundColor(ContextCompat.getColor(this, R.color.team1_background))
                binding.switchTeam.trackTintList = ContextCompat.getColorStateList(this, R.color.switch_track_off_team1)
                binding.switchTeam.thumbTintList = ContextCompat.getColorStateList(this, R.color.switch_thumb_off_team1)
            }
        }


        // CONNECT butonu için click listener
        binding.buttonConnect.setOnClickListener {
            val userName = binding.editTextUserName.text.toString()
            if (userName.isNotEmpty()) {
                val teamName = if (binding.switchTeam.isChecked) getString(R.string.team_2) else getString(R.string.team_1)
                Toast.makeText(this, "Connecting $userName to $teamName", Toast.LENGTH_SHORT).show()
                if (sock == 0) {
                    Toast.makeText(this, "Could not connect to server", Toast.LENGTH_SHORT).show()
                } else {
                    if (sendToServer(sock, binding.switchTeam.isChecked(), userName) == 0) { // -1 is the error code
                        Toast.makeText(this, "User is not allowed", Toast.LENGTH_SHORT).show()
                    } else {
                        Toast.makeText(this, "User is connected", Toast.LENGTH_SHORT).show()
                        val intent = Intent(this@MainActivity, GameActivity::class.java)
                        startActivity(intent)
                    }
                }

            } else {
                Toast.makeText(this, getString(R.string.enter_a_name), Toast.LENGTH_SHORT).show()
            }
        }

        sock = StaticGameDatas.sock
//        sock = connectToServer("10.1.237.77", 8080)
//        Log.i("Socket", "Socket connected with id: $sock")
//        sock = connectToServer("192.168.64.95", 8080)
    }

//    disconnect when the app is closed
    override fun onDestroy() {
        super.onDestroy()
        disconnectFromServer(sock)
    }

    fun updateUserInfosAndSock(case: Int, id: Int, team: Int, name: String, health: Int, kills: Int, deaths: Int) {

        when (case) {
            0 ->
            {
                StaticGameDatas.user = User(id, team, name)
                StaticGameDatas.sock = sock
            }
            1 ->
            {
                // Update the TextViews in the UI with the new kills and deaths
                val killsTextView = findViewById<TextView>(R.id.tvKills)
                val deathsTextView = findViewById<TextView>(R.id.tvDeaths)
                killsTextView.text = "Kills: $kills"
                deathsTextView.text = "Deaths: $deaths"
            }

        }


    }

    /**
     * A native method that is implemented by the 'cubuk_deneme1' native library,
     * which is packaged with this application.
     */
//    external fun stringFromJNI(): String
//
//    companion object {
//        // Used to load the 'cubuk_deneme1' library on application startup.
//        init {
//            System.loadLibrary("cubuk_deneme1")
//        }
//    }
}