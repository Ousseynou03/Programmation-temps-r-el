// Implémentation des bibiothéques
#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h> /* pour htons et inet_aton */


//Pour crée une communication, on utilise l'appel systéme socket()

int main(int argc, char *argv[]){
   // int DescripteurSocket;
    struct sockaddr_in PointDeRencontreDistant;
    socklen_t longueurAdresse;

    //Début de la 1ére étape 
    //Créer une communication

    int DescripteurSocket = socket(PF_INET, SOCK_STREAM, 0);
    //0 indique que l'on utilisera le protocole par défaut associé à SOCK_STREAM soit TCP
    //Testons à présent la valeur renvoyé par l'appel systéme 

    if(DescripteurSocket < 0){
        perror("socket"); //Affiche le message d'erreur
        exit(-1);

    }
//Fin  de la 1ére étape
    printf("Socket crée avec succés ! %d\n", DescripteurSocket);


    //Début Etape N°2
    longueurAdresse = sizeof(PointDeRencontreDistant);
    //Initialisation à 0 de la structure sockaddre_in
    memset(&PointDeRencontreDistant, 0, longueurAdresse);
    PointDeRencontreDistant.sin_family=PF_INET;
    //On choisit le numéro de port d'écoute du serveur
    PointDeRencontreDistant.sin_port=htons(IPPORT_USERRESERVED);
    //On choisit l'adresse IPv4 du serveur
    inet_aton("127.0.0.1", &PointDeRencontreDistant.sin_addr);

    //Début de la connexion vers le processus serveur distant
    if((connect(DescripteurSocket, (struct sockaddr *)&PointDeRencontreDistant, longueurAdresse )) == -1);
    {
        perror("connect");
          //Fermeture de la ressource
        close(DescripteurSocket);
        exit(-2);

    }

    printf("Connexion au serveur réussi avec succés");
    close(DescripteurSocket);

  


    return 0;
}
