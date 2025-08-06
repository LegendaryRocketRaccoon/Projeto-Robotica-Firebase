#ifndef FIREBASE_H
#define FIREBASE_H

#include <Firebase_ESP_Client.h>

// Chaves e URL
#define API_KEY "AIzaSyAdKDXizjq1CKXLMocwbqMAgF3cvS6aYn4"
#define DATABASE_URL "https://projetoglo-default-rtdb.firebaseio.com"

// Objetos do Firebase
extern FirebaseData fbdo;
extern FirebaseAuth auth;
extern FirebaseConfig config;

void inicializarFirebase();
void verificarComandosFirebase();
void enviarEstadoParaFirebase();

#endif