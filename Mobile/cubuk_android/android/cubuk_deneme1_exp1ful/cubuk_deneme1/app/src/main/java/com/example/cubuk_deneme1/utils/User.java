package com.example.cubuk_deneme1.utils;

public class User {
    private int userId;
    private int teamId;
    private String userName;
    private int health;
    private int kills;
    private int deaths;

    public User(int userId, int teamId, String userName) {
        this.userId = userId;
        this.teamId = teamId;
        this.userName = userName;
        this.health = 100;
        this.kills = 0;
        this.deaths = 0;
    }

    public int getUserId() {
        return userId;
    }

    public int getTeamId() {
        return teamId;
    }

    public String getUserName() {
        return userName;
    }

    public int getHealth() {
        return health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public int getKills() {
        return kills;
    }

    public void setKills(int kills) {
        this.kills = kills;
    }

    public int getDeaths() {
        return deaths;
    }

    public void setDeaths(int deaths) {
        this.deaths = deaths;
    }
}
