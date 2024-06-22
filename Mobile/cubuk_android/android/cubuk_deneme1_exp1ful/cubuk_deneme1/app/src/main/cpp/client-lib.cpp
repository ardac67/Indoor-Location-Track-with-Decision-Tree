//
// Created by btsts on 26.04.2024.
//

#include <jni.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <android/log.h>
#include "json.hpp"
#include <sstream>
#include <regex>

using namespace nlohmann;

int userId = -1;
void updateUser(JNIEnv* env, jobject thiz, json& data);

extern "C" JNIEXPORT jint JNICALL
Java_com_example_cubuk_1deneme1_LoginActivity_connectToServer(
        JNIEnv* env,
        jobject /* this */,
        jstring ip,
        jint port) {

    const char *ipStr = env->GetStringUTFChars(ip, nullptr);
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Client", "Socket creation error");
        return 0;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, ipStr, &serv_addr.sin_addr)<=0) {
        __android_log_print(ANDROID_LOG_ERROR, "Client", "Invalid address/ Address not supported");
        return 0;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Client", "Connection Failed");
        return 0;
    }

//    const char *hello = "Hello from client";
//    send(sock , hello , strlen(hello) , 0 );
//    __android_log_print(ANDROID_LOG_INFO, "Client", "Hello message sent");
//    int valread = read( sock , buffer, 1024);
//    __android_log_print(ANDROID_LOG_INFO, "Client", "%s\n",buffer );
    env->ReleaseStringUTFChars(ip, ipStr);

    return sock;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_cubuk_1deneme1_LoginActivity_disconnectFromServer(
        JNIEnv* env,
        jobject /* this */,
        jint sock) {
    close(sock);
    return JNI_TRUE;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_cubuk_1deneme1_MainActivity_disconnectFromServer(
        JNIEnv* env,
        jobject /* this */,
        jint sock) {
    close(sock);
    return JNI_TRUE;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_cubuk_1deneme1_MainActivity_sendToServer(
        JNIEnv* env,
        jobject thiz /* this */,
        jint sock,
        jboolean teamId,
        jstring userName) {

    if (sock <= 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Client", "Invalid socket");
        return 0;
    }

    const char *userNameCStr = env->GetStringUTFChars(userName, nullptr);

    // Manually create JSON string
    std::string jsonStr = "{\"teamId\":";
    jsonStr += teamId ? "\"1\"" : "\"0\"";
    jsonStr += ", \"userName\":\"";
    jsonStr += userNameCStr;
    jsonStr += "\", \"requestType\":\"apk_player_create\"}";

    // Release the memory for userName string
    env->ReleaseStringUTFChars(userName, userNameCStr);

    // Send JSON string to the server
    ssize_t sentBytes = send(sock, jsonStr.c_str(), jsonStr.length(), 0);
    if (sentBytes < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Client", "Failed to send data to server");
        return 0;
    }

    while (true) {
        char buffer[1024] = {0};
        int valread = read(sock, buffer, 1024);
        if (valread < 0) {
            __android_log_print(ANDROID_LOG_ERROR, "Client", "Failed to read data from server");
            return 0;
        }

        if (valread > 0) {
            __android_log_print(ANDROID_LOG_INFO, "Client", "%s\n", buffer);
        }

        if (strcmp(buffer, "-1") == 0)
        {
            __android_log_print(ANDROID_LOG_INFO, "ÇIKIŞ BAŞARILI", "%s\n", buffer);

            return JNI_FALSE;
        }
        else
        {
            try {
                json response = json::parse(buffer);
                if (response["type"] == "create")
                {
                    updateUser(env, thiz, response);
                    __android_log_print(ANDROID_LOG_INFO, "Client", "Update user object%s\n", buffer);

                    userId = std::stoi(response["id"].get<std::string>());
                }
                break;
            } catch (...) {
                return JNI_FALSE;
            }
        }

    }

    return JNI_TRUE;
}


extern "C" JNIEXPORT jint JNICALL
Java_com_example_cubuk_1deneme1_GameActivity_sendHitToServer(
        JNIEnv* env,
        jobject thiz,
        jint sock,
        jint userId,
        jstring enemyId) {

    if (sock <= 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Client", "Invalid socket");
        return 0;
    }

    // Manually create JSON string
    std::string jsonStr = "{\"from\":\"";
    jsonStr += std::to_string(userId);
    jsonStr += "\", \"to\":\"";
    jsonStr += env->GetStringUTFChars(enemyId, nullptr);;
    jsonStr += "\", \"requestType\":\"hit\"}";

    // Send JSON string to the server
    ssize_t sentBytes = send(sock, jsonStr.c_str(), jsonStr.length(), 0);
    if (sentBytes < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "Client", "Failed to send data to server");
        return 0;
    }

    while (true) {
        char buffer[1024] = {0};
        int valread = read(sock, buffer, 1024);
        if (valread < 0) {
            __android_log_print(ANDROID_LOG_ERROR, "Client", "Failed to read data from server");
            return 0;
        }

        if (valread > 0) {
            __android_log_print(ANDROID_LOG_INFO, "Client", "%s\n", buffer);
        }

        if (strcmp(buffer, "-1") == 0) {
            __android_log_print(ANDROID_LOG_INFO, "BAŞARILI", "%s\n", buffer);
            return JNI_FALSE;
        } else {
            __android_log_print(ANDROID_LOG_INFO, "RecHit", "%s\n", buffer);
            try {
                std::string data(buffer);
                std::regex re(R"(\{(?:[^{}]|\{(?:[^{}]|\{[^{}]*\})*\})*\})"); // Regex to match JSON objects
                std::sregex_iterator next(data.begin(), data.end(), re);
                std::sregex_iterator end;

                while (next != end) {
                    std::smatch match = *next;
                    std::string json_str = match.str();
                    json response = json::parse(json_str);
                    next++;

                    std::string type = response["type"];
                    if (response["type"] == "being_hit") {
                        std::string status = response["status"];
                        std::string from = response["from"];
                        std::string to = response["to"];
                        if (status == "dead") {
                            int from_death_count = response["from_death_count"];
                            int from_kill_count = response["from_kill_count"];
                            int to_death_count = response["to_death_count"];
                            int to_kill_count = response["to_kill_count"];

                            jclass clazz = env->GetObjectClass(thiz);

                            jmethodID updateMethod = env->GetMethodID(clazz, "updateKillDeathView", "(II)V");
                            if (updateMethod == nullptr) {
                                __android_log_print(ANDROID_LOG_ERROR, "JNI", "Cannot find update method");
                                return JNI_FALSE;
                            }

                            if (userId == std::stoi(from)) {
                                env->CallVoidMethod(thiz, updateMethod, from_kill_count, from_death_count);
                            } else if (userId == std::stoi(to)) {
                                env->CallVoidMethod(thiz, updateMethod, to_kill_count, to_death_count);
                            }

                            __android_log_print(ANDROID_LOG_INFO, "Client", "Player %s is dead. Death count: %d, Kill count: %d\n", from.c_str(), from_death_count, from_kill_count);
                            __android_log_print(ANDROID_LOG_INFO, "Client", "Player %s death count: %d, Kill count: %d\n", to.c_str(), to_death_count, to_kill_count);

                            // Here, you could call a method to update your UI or internal state with this information
                        }
//                        else if (status == "hit") {
//                        int from_health = response["from_health"];
//                            int to_health = response["to_health"];

//                            __android_log_print(ANDROID_LOG_INFO, "Client", "Player %s hit Player %s. Player %s health: %d, Player %s health: %d\n", from.c_str(), to.c_str(), from.c_str(), 0, to.c_str(), to_health);

                            // Here, you could call a method to update your UI or internal state with this information
//                        }
                    }
                }
            } catch (json::parse_error& e) {
                __android_log_print(ANDROID_LOG_ERROR, "Client", "JSON parse error: %s\n", e.what());
            } catch (const std::exception& e) {
                __android_log_print(ANDROID_LOG_ERROR, "Client", "Exception: %s\n", e.what());
            } catch (...) {
                __android_log_print(ANDROID_LOG_ERROR, "Client", "Unknown error occurred");
            }
            break;
        }

    }

    return JNI_TRUE;
}

void updateUser(JNIEnv* env, jobject thiz, json& data) {
    jclass userClass = env->FindClass("com/example/cubuk_deneme1/utils/User");
    if (userClass == nullptr) return;

    jmethodID constructor = env->GetMethodID(userClass, "<init>", "(IILjava/lang/String;)V");
    if (constructor == nullptr) return;

    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == nullptr) return;

    jmethodID updateMethod = env->GetMethodID(clazz, "updateUserInfosAndSock", "(IIILjava/lang/String;III)V");
    if (updateMethod == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "JNI", "Cannot find update method");
        return;
    }

    jint id = std::stoi(data["id"].get<std::string>());
    jstring name = env->NewStringUTF(data["name"].get<std::string>().c_str());
    jint team = std::stoi(data["team"].get<std::string>());

    __android_log_print(ANDROID_LOG_INFO, "Client", "Json parsed with these %d, %s, %d\n", std::stoi(data["id"].get<std::string>()), data["name"].get<std::string>().c_str(), std::stoi(data["team"].get<std::string>()));

    jobject userObject = env->NewObject(userClass, constructor, id, team, name);
    if (userObject == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, "JNI", "Failed to create a User object");
        env->DeleteLocalRef(name); // Clean up the jstring object
        return;
    }

    env->CallVoidMethod(thiz, updateMethod, 0, id, team, name, 0, 0, 0);

    // Remember to release local references when you're done
    env->DeleteLocalRef(userObject);
    env->DeleteLocalRef(name);
}
