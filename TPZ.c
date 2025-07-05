 /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             Réalisée par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/

  /*-------------------------------------------------------------------------*/

  /*                 TP 2 Khawarizm : Optimized Word Search                  */

  /*                           Réalisé par :                                 */

  /*                           Charef Iyad                                   */

  /*                   Section : D       Groupe : 13                         */

  /*-------------------------------------------------------------------------*/

   
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>

  typedef int bool ;
  typedef char * string255 ;

  #define True 1
  #define False 0

  // Simulation parameters
   #define SIM_M_ITERATIONS 10     
   #define SIM_N_BUILD_WORDS 10000  
   #define SIM_N_SEARCH_WORDS 10000 
   #define SIM_N_RANGE_PAIRS 5000   

  /** Implémentation **\: ARBRE BINAIRE DE CHAINES DE CARACTERES**/

  /** Arbres de recherche binaire **/

  typedef string255 Typeelem_As   ;
  typedef struct Noeud_As * Pointeur_As ;

  struct Noeud_As
    {
      Typeelem_As  Val ;
      Pointeur_As Fg ;
      Pointeur_As Fd ;
      Pointeur_As Pere ;
     } ;

  Typeelem_As Info_As( Pointeur_As P )
    { return P->Val;   }

  Pointeur_As Fg_As( Pointeur_As P)
    { return P->Fg ; }

  Pointeur_As Fd_As( Pointeur_As P)
    { return P->Fd ; }

  Pointeur_As Pere_As( Pointeur_As P)
    { return P->Pere ; }

  void Aff_info_As ( Pointeur_As P, Typeelem_As Val)
    {
       strcpy( P->Val , Val );
    }

  void Aff_fg_As( Pointeur_As P, Pointeur_As Q)
    { P->Fg =  Q;  }

  void Aff_fd_As( Pointeur_As P, Pointeur_As Q)
    { P->Fd =  Q ; }

  void Aff_pere_As( Pointeur_As P, Pointeur_As Q)
    { P->Pere =  Q ; }

  void Creernoeud_As( Pointeur_As *P)
    {
      *P = (struct Noeud_As *) malloc( sizeof( struct Noeud_As))   ;
      (*P)->Val = malloc(255 * sizeof(string255));
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_As( Pointeur_As P)
    { free( P ) ; }

  // free trees
  void Destroy_As(Pointeur_As *R_ptr) {
    if (R_ptr == NULL || *R_ptr == NULL) return;
    
    Pointeur_As current_node = *R_ptr;
    Pointeur_As fg_child = Fg_As(current_node);
    Pointeur_As fd_child = Fd_As(current_node);

    Destroy_As(&fg_child); 
    Destroy_As(&fd_child); 
    
    if (Info_As(current_node)) { 
        free(Info_As(current_node)); 
    }
    Liberernoeud_As(current_node); 
    *R_ptr = NULL;
   }

  /** Implémentation **\: FICHIER 
  /* Traitement des fichiers ouverts */

  /* Traitement des fichiers ouverts */

  struct _Noeud
    {
      FILE * Var_fich ;
      char * Nom_fich ;
      int Sauv_pos;
      struct _Noeud *Suiv ;
    } ;

  typedef struct _Noeud * _Ptr_Noeud;

  _Ptr_Noeud  _Pile_ouverts  = NULL;

  /* Teste si un fichier est ouvert */
  _Ptr_Noeud _Ouvert ( char * Fp)
    {
      _Ptr_Noeud P;
      bool Trouv ;
      P = _Pile_ouverts; Trouv = False ;
      while ((P != NULL) && ! Trouv )
        if ( strcmp(P->Nom_fich, Fp) == 0)
        Trouv = True;
        else P = P->Suiv;
      return P;
    }

  /* Ajouter un fichier ouvert */
  void _Empiler_ouvert ( char *Fp, FILE *Fl)
    {
      _Ptr_Noeud  P ;
      P = (_Ptr_Noeud) malloc( sizeof( struct _Noeud)) ;
      P->Nom_fich = Fp;
      P->Var_fich = Fl;
      P->Suiv = _Pile_ouverts;
      _Pile_ouverts = P;
    }

  /* Supprimer un fichier ouvert et rendre son nom*/
  char * _Depiler_ouvert ( FILE *Fl)
    {
      char * Fp = malloc (100);
      _Ptr_Noeud P,  Prec  ;
      P= _Pile_ouverts;
      Prec = NULL;
      while (P->Var_fich != Fl )
        { Prec = P ; P = P->Suiv ;}
      strcpy(Fp, P->Nom_fich);
      if (Prec != NULL)
        Prec->Suiv = P->Suiv;
      else _Pile_ouverts = P->Suiv;
      free (P);
      return Fp ;
    }


  /** Fichiers **/

  typedef char _Tx[255];
  typedef string255 Typestruct1_s;
  typedef _Tx Typestruct1_s_Buf;


  /** Machine abstaite sur les fichiers **/

  void Ouvrir_s ( FILE **s , char *Fp , char * Mode )
    {
      _Ptr_Noeud P = _Ouvert(Fp);
      if ( P != NULL )
      /* Le fichier est d?j? ouvert */
        {
         P->Sauv_pos = ftell (P->Var_fich);
         fclose(P->Var_fich);
        }
      /* Le fichier est non ouvert */
      if ( strcmp(Mode,"A") == 0)
        *s = fopen(Fp, "r+b");
      else
        *s = fopen(Fp, "w+b");
      _Empiler_ouvert( Fp, *s);
    }

  void Fermer_s ( FILE * s )
    {
      char * Fp = malloc(100);
      _Ptr_Noeud P;
      strcpy(Fp, _Depiler_ouvert(s));
      fclose(s) ;
      /* Ya-til un fichier ouvert avec le m?me nom ?  */
      /* Si Oui, le R?ouvrir ? la position sauvegard?e */
      P =  _Ouvert (Fp);
      if ( P != NULL)
      {
        s = fopen(P->Nom_fich, "r+b");
        fseek(s, P->Sauv_pos, 0);
      }
    }

  void Ecrireseq_s ( FILE * s, Typestruct1_s Buf  )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Ecriredir_s ( FILE * s, Typestruct1_s Buf, int N )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, (long) (N-1)* sizeof(  Typestruct1_s_Buf), 0);
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Lireseq_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      if (fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s) != 0) {
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
      }
    }

  void Liredir_s ( FILE * s, Typestruct1_s Buf, int N)
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      fseek(s, (long) (N-1)* sizeof( Typestruct1_s_Buf), 0 );
      fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s);
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
    }

  void Rajouter_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, 0, 2); /* Fin du fichier */
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  bool Finfich_s (FILE * s)
    {
      long K = ftell(s);
      fseek(s, 0, 2); /* Fin du fichier */
      long K2 = ftell(s);   /* position ? partir du debut */
      if  (K==K2)
        { fseek(s, K, 0); return 1;}
      else
        { fseek(s, K, 0); return 0;}
    }

  int Alloc_bloc_s (FILE * s)
    {
      long K;
      fseek(s, 0, 2); /* Fin du fichier */
      K = ftell(s);   /* position ? partir du debut */
      K = K / sizeof (Typestruct1_s_Buf);
      K ++;
      return(K);
    }


  /** Implémentation **\: FILE DE ARBRES BINAIRES DE CHAINES DE CARACTERES**/
  /** Files d'attente **/

  typedef Pointeur_As Typeelem_FAs ;
  typedef  struct Filedattente_FAs * Pointeur_FAs ;
  typedef  struct Maillon_FAs * Ptliste_FAs ;

  struct Maillon_FAs
    {
      Typeelem_FAs Val ;
      Ptliste_FAs Suiv  ;
    };

  struct Filedattente_FAs
    {
      Ptliste_FAs Tete, Queue ;
    };

  void Creerfile_FAs ( Pointeur_FAs *Fil   )
    {
      *Fil = (struct Filedattente_FAs *) malloc( sizeof( struct Filedattente_FAs)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Filevide_FAs (Pointeur_FAs Fil  )
    { return  Fil->Tete == NULL ;}

  void Enfiler_FAs ( Pointeur_FAs Fil , Typeelem_FAs Val   )
    {
      Ptliste_FAs Q;

      Q = (struct Maillon_FAs *) malloc( sizeof( struct Maillon_FAs))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Filevide_FAs(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Defiler_FAs (Pointeur_FAs Fil, Typeelem_FAs *Val )
    {
      if (! Filevide_FAs(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "File d'attente vide");
    }

  /** Variables du programme principal **/
  int H;
  Pointeur_As R=NULL;
  Pointeur_As R1=NULL;
  Pointeur_As R2=NULL;
  Pointeur_As R3=NULL;
  Pointeur_As P=NULL;
  string255 Word;
  string255 Mot1;
  string255 Mot2;

  /** Fonctions standards **/

  char *Caract ( string255 Ch , int I )
    {
      char *s = malloc(2);
      s[0] = Ch[I-1];
      s[1] = '\0';
      return  s;
    }

  int Max (int a, int b)
    {
      if (a > b) return(a);
      else return(b);
    }

  int Aleanombre( int N )
    { return ( rand() % N ); }

  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = malloc(N+1);

      char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }


    /** Prototypes des fonctions **/

    void Insertbst (string255 *Mot , Pointeur_As *R , bool *Done);
    void Createbst0(Pointeur_As *R_ptr, const char* filename);
    void Createbst1 (Pointeur_As *R_ptr, const char* filename);
    void Createbst2 (Pointeur_As *R_ptr, const char* filename);
    void Createbst3 (Pointeur_As *R_ptr, const char* filename);

    Pointeur_As Ror (Pointeur_As *R);
    Pointeur_As Rol (Pointeur_As *R);
    void Search (Pointeur_As *R_ptr , string255 *Word_param , Pointeur_As *P_out, int *nodes_visited_ptr);

    int Depth (Pointeur_As *R);
    void Count (Pointeur_As *R_ptr);
    void Levelcount (Pointeur_As *R);
    int Nodelevel (Pointeur_As *R , Pointeur_As *P);
    void Levelbylevel (Pointeur_As *R);
    void Searchbst (Pointeur_As *R1 , Pointeur_As *R2 , Pointeur_As *R3 , string255 *Mot , Pointeur_As *P);
    void Searchbst1 (Pointeur_As *R , string255 *Word , Pointeur_As *P, int *nodes_visited_ptr);
    void Searchbst2 (Pointeur_As *R , string255 *Word , Pointeur_As *P, int *nodes_visited_ptr);
    void Searchbst3 (Pointeur_As *R , string255 *Word , Pointeur_As *P, int *nodes_visited_ptr);
    void Rangebst (Pointeur_As *R1 , Pointeur_As *R2 , Pointeur_As *R3 , string255 *Mot1 , string255 *Mot2);
    void Rangequery (Pointeur_As *R_ptr , string255 *A_param , string255 *B_param, int *nodes_traversed_ptr);
    Pointeur_As Next_inordre (Pointeur_As *P_curr_ptr, int *nodes_accessed_ptr);
    void Searchsmallest (Pointeur_As *R_ptr_param , string255 *Word_param , Pointeur_As *P_out, int *nodes_visited_ptr);

    void Inorder_traversal (Pointeur_As *R);
    void File_gen_word();
    void File_gen_N_words(const char* filename, int num_words);
    void Generate_N_Word_Pairs_File(const char* filename, int num_pairs);
    void RangeSearch_Triplet_Sim(Pointeur_As R1_in, Pointeur_As R2_in, Pointeur_As R3_in, string255 Mot1_in, string255 Mot2_in, int *nodes_traversed_ptr);
    void Simulate_Single_Word_Search_Efficiency();
    void Simulate_Range_Search_Efficiency();
    void Menu();

// Insertbst (+parent link)
  void Insertbst (string255 *Mot , Pointeur_As *R , bool *Done) {
    Pointeur_As P_child=NULL; *Done = False ;
    if( ( *R == NULL )) { Creernoeud_As (R); Aff_info_As (*R , *Mot ); Aff_pere_As (*R , NULL ); *Done = True ; }
    else {
      if( (strcmp( Info_As ( *R ), *Mot) == 0 )) { *Done  =  True ;} 
      else {
        if( (strcmp( Info_As ( *R ), *Mot) > 0 )) {
          P_child = Fg_As ( *R ) ; Insertbst (Mot , &P_child , Done ) ;
          if (*Done) { 
            Aff_fg_As ( *R , P_child ) ; if (P_child) Aff_pere_As ( P_child , *R ) ;
          }
        } else {
          P_child = Fd_As ( *R ) ; Insertbst (Mot , &P_child , Done ) ;
          if (*Done) {
            Aff_fd_As ( *R , P_child ) ; if (P_child) Aff_pere_As ( P_child , *R ) ;
          }
        } ;
      } ;
    } ;
  }
// NEW: Createbst0 
  void Createbst0 (Pointeur_As *R_ptr, const char* filename) {
    FILE *F; Typestruct1_s S_buf ; bool Done_insert;
    S_buf = malloc(256 * sizeof(char)); 
    if (!S_buf) { perror("malloc failed for S_buf in Createbst0"); exit(1); }

    Ouvrir_s (&F , (char*)filename , "A" ) ; // "A" read existing file
    if (F == NULL) {
      printf("Error: Could not open file %s in Createbst0\n", filename);
      free(S_buf); return;
    }
    S_buf[0] = '\0'; Lireseq_s(F, S_buf);
    while( !Finfich_s(F) && S_buf[0] != '\0' ) {
      Insertbst (&S_buf , R_ptr , &Done_insert ) ; 
      S_buf[0] = '\0'; Lireseq_s (F, S_buf ) ;
    } ;
    Fermer_s (F) ;
    free(S_buf);
  }
//  Createbst1 takes filename
void Createbst1 (Pointeur_As *R, const char* filename)
    {
      /** Variables locales **/
      Pointeur_As P = NULL;
      Pointeur_As Q = NULL;
      FILE *F;
      Typestruct1_s S ;
      bool Done;
      char *temp_caract_res = NULL;

      /** Corps du module **/
     S = malloc(256 * sizeof(char)); // buffer
     if (!S) {
         printf("Error: malloc failed for S in Createbst1\n");
         return;
     }

     // (char*)filename 
     Ouvrir_s (&F , (char*)filename , "A" ) ;
     if (F == NULL) {
         printf("Error opening %s in Createbst1\n", filename);
         free(S); 
         return;
     }

     S[0] = '\0'; // Initialize S
     Lireseq_s ( F , S ) ;

     while( !Finfich_s(F) && S[0] != '\0' ) {
       Insertbst ( &S , R , &Done ) ;
       Search ( R , &S , &P , NULL ) ;

       if( P != NULL ) { 
         temp_caract_res = Caract ( S , 1 );

         if ( temp_caract_res != NULL ) { 
           // Rotation block: if condition met, rotate P to the root of the tree
           if( (strcmp( temp_caract_res, "Y") == 0) || (strcmp( temp_caract_res, "Z") == 0) || (strcmp( temp_caract_res, "a") == 0) ) {
             while( Pere_As ( P ) != NULL ) {
               Q  =  Pere_As ( P ) ; 
               if( P == Fg_As ( Pere_As ( P ) ) ) P = Ror ( &P ) ; else P = Rol ( &P ) ;
               if( Q == *R ) *R = P ; // Update the tree root if P original parent was root
             } ;
           }
           free(temp_caract_res); // Free Caract
           temp_caract_res = NULL;
         }
       } ;

       S[0] = '\0'; // reinitialize S
       Lireseq_s ( F , S ) ;
     } ;

     Fermer_s ( F ) ;
     free(S); // Free S
     S = NULL;
    }

// Createbst2 takes filename
void Createbst2 (Pointeur_As *R, const char* filename)
    {
      /** Variables locales **/
      int L;
      int Cpt;
      Pointeur_As P = NULL;
      Pointeur_As Q = NULL;
      FILE *F;
      Typestruct1_s S ;
      bool Done;
      char *temp_caract_res = NULL;

      /** Corps du module **/
     S = malloc(256 * sizeof(char)); 
     if (!S) {
         printf("Error: malloc failed for S in Createbst2\n");
         return;
     }

  
     Ouvrir_s (&F , (char*)filename , "A" ) ;
     if (F == NULL) {
         printf("Error opening %s in Createbst2\n", filename);
         free(S); 
         return;
     }

     S[0] = '\0'; 
     Lireseq_s ( F , S ) ;

     while( !Finfich_s(F) && S[0] != '\0' ) {
       Insertbst ( &S , R , &Done ) ;
       Search ( R , &S , &P , NULL ) ;

       if( P != NULL ) { 
         temp_caract_res = Caract ( S , 1 );

         if ( temp_caract_res != NULL ) {
           // First rotation block: if condition met, rotate P to the root of the tree
           if( ( (strcmp( temp_caract_res, "Y") > 0  ) || (strcmp( temp_caract_res, "Z") > 0  ) || (strcmp( temp_caract_res, "a") > 0  ) )) {
             while( ( Pere_As ( P ) != NULL ) ) {
               Q  =  Pere_As ( P ) ; 
               if( ( P == Fg_As ( Pere_As ( P ) ) )) {
                 P  =  Ror ( & P ) ;
                 }
               else
                 {
                 P  =  Rol ( & P ) ;
               } ;
               if( ( Q == *R )) { 
                 *R  =  P ;       
               } ;
             } ;
           } ;

           // Second rotation block: if condition met, rotate P L/2 times towards the root
           if( ( (strcmp( temp_caract_res, "Y") == 0  ) || (strcmp( temp_caract_res, "Z") == 0  ) || (strcmp( temp_caract_res, "a") == 0  ) )) {
             L  =  Nodelevel ( R , &P ) ;
             L  =  L / 2 ;
             Cpt  =  0 ;
             while( ( Pere_As ( P ) != NULL ) && ( Cpt < L ) ) {
               Q  =  Pere_As ( P ) ; 
               if( ( P == Fg_As ( Pere_As ( P ) ) )) {
                 P  =  Ror ( & P ) ;
                 }
               else
                 {
                 P  =  Rol ( & P ) ;
               } ;
               if( ( Q == *R )) { 
                 *R  =  P ;        
               } ;
               Cpt  =  Cpt + 1;
             } ;
           } ;

           free(temp_caract_res); 
           temp_caract_res = NULL;
         }
       } ;

       S[0] = '\0'; 
       Lireseq_s ( F , S ) ;
     } ;

     Fermer_s ( F ) ;
     free(S); 
     S = NULL;
    }
//  Createbst3 takes filename
void Createbst3 (Pointeur_As *R, const char* filename)
    {
      /** Variables locales **/
      Pointeur_As P = NULL;
      Pointeur_As Q = NULL;
      FILE *F;
      Typestruct1_s S ;
      bool Done;
      char *temp_caract_res = NULL;

      /** Corps du module **/
     S = malloc(256 * sizeof(char)); // Allocate buffer for S
     if (!S) {
         printf("Error: malloc failed for S in Createbst3\n");
         return;
     }

  
     Ouvrir_s (&F , (char*)filename , "A" ) ;
     if (F == NULL) {
         printf("Error opening %s in Createbst3\n", filename);
         free(S); 
         return;
     }

     S[0] = '\0'; 
     Lireseq_s ( F , S ) ;

     while( !Finfich_s(F) && S[0] != '\0' ) {
       Insertbst ( &S , R , &Done ) ;
       Search ( R , &S , &P , NULL ) ;

       if( P != NULL ) { 
         temp_caract_res = Caract ( S , 1 );

         if ( temp_caract_res != NULL ) { 
           // Rotation block: if condition met (char is NOT Y, Z, or a), rotate P to the root
           if( !( (strcmp( temp_caract_res, "Y") == 0) || (strcmp( temp_caract_res, "Z") == 0) || (strcmp( temp_caract_res, "a") == 0) ) ) {
             while( Pere_As ( P ) != NULL ) {
               Q  =  Pere_As ( P ) ; 
               if( P == Fg_As ( Pere_As ( P ) ) ) P = Ror ( &P ) ; else P = Rol ( &P ) ;
               if( Q == *R ) *R = P ; 
             } ;
           }
           free(temp_caract_res);
           temp_caract_res = NULL;
         }
       } ;

       S[0] = '\0'; 
       Lireseq_s ( F , S ) ;
     } ;

     Fermer_s ( F ) ;
     free(S); 
     S = NULL;
    }
/*-----------------------------------------------------------*/
  Pointeur_As Ror (Pointeur_As *R) 
    {
      /** Variables locales **/
      Pointeur_As Ror2 =NULL;
      Pointeur_As A=NULL;

      /** Corps du module **/
     A  =  Pere_As ( *R ) ;
     *R  =  Fg_As ( A ) ;
     if( ( *R == NULL )) {
       Ror2  =  A ;
       }
     else
       {
       Aff_fg_As ( A , Fd_As ( *R ) ) ;
       if( Fd_As ( *R ) != NULL) {
         Aff_pere_As ( Fd_As ( *R ) , A ) ;
        
       } ;
       Aff_fd_As ( *R , A ) ;
       Aff_pere_As ( *R , Pere_As ( A ) ) ;
       if( ( Pere_As ( A ) != NULL )) {
         if( ( Fg_As ( Pere_As ( A ) ) == A )) {
           Aff_fg_As ( Pere_As ( A ) , *R ) ;
           }
         else
           {
           Aff_fd_As ( Pere_As ( A ) , *R ) ;
          
         } ;
         }
       else
         {
         Aff_pere_As ( *R , NULL ) ;
        
       } ;
       Aff_pere_As ( A , *R ) ;
       Ror2  =  *R ;
      
     } ;
    
     return Ror2 ;
    }
  /*-----------------------------------------------------------*/
  Pointeur_As Rol (Pointeur_As *R) 
    {
      /** Variables locales **/
      Pointeur_As Rol2 =NULL;
      Pointeur_As A=NULL;

      /** Corps du module **/
     A  =  Pere_As ( *R ) ;
     *R  =  Fd_As ( A ) ;
     if( ( *R == NULL )) {
       Rol2  =  *R ;
       }
     else
       {
       Aff_fd_As ( A , Fg_As ( *R ) ) ;
       if( Fg_As ( *R ) != NULL) {
         Aff_pere_As ( Fg_As ( *R ) , A ) ;
        
       } ;
       Aff_fg_As ( *R , A ) ;
       Aff_pere_As ( *R , Pere_As ( A ) ) ;
       if( ( Pere_As ( A ) != NULL )) {
         if( ( Fg_As ( Pere_As ( A ) ) == A )) {
           Aff_fg_As ( Pere_As ( A ) , *R ) ;
           }
         else
           {
           Aff_fd_As ( Pere_As ( A ) , *R ) ;
          
         } ;
         }
       else
         {
         Aff_pere_As ( *R , NULL ) ;
        
       } ;
       Aff_pere_As ( A , *R ) ;
       Rol2  =  *R ;
      
     } ;
    
     return Rol2 ;
    }
  /*-----------------------------------------------------------*/
// Search with node counting
  void Search (Pointeur_As *R_ptr , string255 *Word_param , Pointeur_As *P_out, int *nodes_visited_ptr) {
    Pointeur_As _Px1_fg=NULL; Pointeur_As _Px2_fd=NULL; 
    
    if (nodes_visited_ptr != NULL && R_ptr != NULL && *R_ptr != NULL) { (*nodes_visited_ptr)++; }

    if( ( R_ptr == NULL || *R_ptr == NULL )) { *P_out = NULL ; } 
    else {
      if(strcmp( Info_As ( *R_ptr ), *Word_param) == 0 ) { *P_out = *R_ptr ; }
      else {
        if(strcmp( Info_As ( *R_ptr ), *Word_param) > 0 ) {
          _Px1_fg = Fg_As ( *R_ptr ) ; Search ( &_Px1_fg, Word_param , P_out, nodes_visited_ptr ) ;
        } else {
          _Px2_fd = Fd_As ( *R_ptr ) ; Search ( &_Px2_fd, Word_param , P_out, nodes_visited_ptr ) ;
        } ;
      } ;
    } ;
  }
 /*-----------------------------------------------------------*/
  int  Depth (Pointeur_As *R) 
    {
      /** Variables locales **/
      int  Depth2 ;
      int Left;
      int Right;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *R == NULL )) {
       Depth2  =  - 1 ;
       }
     else
       {
       _Px1 =  Fg_As ( *R ) ;
       Left  =  Depth ( &_Px1) ;
       _Px2 =  Fd_As ( *R ) ;
       Right  =  Depth ( &_Px2) ;
       Depth2  =  Max ( Left , Right ) + 1 ;
      
     } ;
    
     return Depth2 ;
    }
//  corrected print
  void Count (Pointeur_As *R_ptr) { 
    Pointeur_As N_node=NULL; Pointeur_FAs Q_file=NULL; int Cpt_count; char* temp_caract_res;
    Cpt_count = 0 ; Creerfile_FAs (&Q_file ) ;
    if( Q_file == NULL) { return; }
    if( ( R_ptr != NULL && *R_ptr != NULL )) { Enfiler_FAs ( Q_file , *R_ptr ) ; }
    
    while( !Filevide_FAs ( Q_file )) {
      Defiler_FAs ( Q_file , &N_node ) ;
      if (N_node == NULL) continue; 
      
      temp_caract_res = Caract(Info_As(N_node), 1);
      if( temp_caract_res && ((strcmp(temp_caract_res, "Y")==0) || (strcmp(temp_caract_res, "Z")==0) || (strcmp(temp_caract_res, "a")==0)) ) Cpt_count++;
      if(temp_caract_res) free(temp_caract_res);
      
      if( Fg_As ( N_node ) != NULL) Enfiler_FAs ( Q_file , Fg_As ( N_node ) ) ;
      if( Fd_As ( N_node ) != NULL) Enfiler_FAs ( Q_file , Fd_As ( N_node ) ) ;
    } ;
    printf ( " The number of words starting with Y, Z, or a: %d\n", Cpt_count );

    if(Q_file) free(Q_file); 
  }
//  print fix
/*-------------------------------------------------------------*/
  void Levelcount (Pointeur_As *R)
    {
      /** Variables locales **/
      Pointeur_As N=NULL;
      Pointeur_FAs Q=NULL;
      int Cpt;
      int Level;
      string255 C;

      /** Corps du module **/
     C = malloc(255 * sizeof(char));
     Cpt  =  0 ;
     Level  =  - 1 ;
     Creerfile_FAs (& Q ) ;
     if( ( *R != NULL )) {
       Enfiler_FAs ( Q , *R ) ;
      
     } ;
     while( ! Filevide_FAs ( Q )) {
       Defiler_FAs ( Q , &N ) ;
       strcpy (C,   Info_As ( N )) ;
       if( ( Nodelevel ( & *R , & N ) > Level )) {
         if( ( Level >= 0 )) {
           printf ( " Level %d: The number of words starting with Y, Z, or a: %d\n", Level, Cpt ) ;
           printf ( " ---------------------------------------------------------\n" ) ;
          
         } ;
         Cpt  =  0 ;
         Level  =  Nodelevel ( & *R , & N ) ;
        
       } ;
      /*ECRIRE (INFO(N)); */
       if( ( (strcmp( Caract ( C , 1 ), "Y") == 0  ) || (strcmp( Caract ( C , 1 ), "Z") == 0  ) || (strcmp( Caract ( C , 1 ), "a") == 0  ) )) {
         Cpt  =  Cpt + 1 ;
        
       } ;
       if( Fg_As ( N ) != NULL) {
         Enfiler_FAs ( Q , Fg_As ( N ) ) ;
        
       } ;
       if( Fd_As ( N ) != NULL) {
         Enfiler_FAs ( Q , Fd_As ( N ) ) ;
        
       } ;
      
 } ;
     if( ( Level >= 0 )) {
       printf ( " Level %d: The number of words starting with Y, Z, or a: %d\n", Level, Cpt ) ;
       printf ( " ---------------------------------------------------------\n" ) ;
     } ;
    
    }
 /*-------------------------------------------------------------*/
  int  Nodelevel (Pointeur_As *R , Pointeur_As *P) 
    {
      /** Variables locales **/
      int  Nodelevel2 ;
      Pointeur_As Q=NULL;
      bool Found;
      int Level;

      /** Corps du module **/
     Level  =  - 1 ;
     Found  =  False ;
     Q  =  *R ;
     while( ( ( Q != NULL ) && ( ! Found ) )) {
       Level  =  Level + 1 ;
       if( (strcmp( Info_As ( Q ), Info_As ( *P )) == 0  )) {
         Found  =  True ;
         }
       else
         {
         if( (strcmp( Info_As ( Q ), Info_As ( *P )) < 0  )) {
           Q  =  Fd_As ( Q ) ;
           }
         else
           {
           Q  =  Fg_As ( Q ) ;
          
         } ;
        
       } ;
      
 } ;
     Nodelevel2  =  Level ;
    
     return Nodelevel2 ;
    }
  /*-----------------------------------------------------------------*/
  void Levelbylevel (Pointeur_As *R)
    {
      /** Variables locales **/
      Pointeur_As N=NULL;
      Pointeur_FAs Q=NULL;

      /** Corps du module **/
     Creerfile_FAs (& Q ) ;
     if( ( *R != NULL )) {
       Enfiler_FAs ( Q , *R ) ;
      
     } ;
     while( ! Filevide_FAs ( Q )) {
       Defiler_FAs ( Q , &N ) ;
       printf ( " %s", Info_As(N) ) ;
       printf("\n");
       if( Fg_As ( N ) != NULL) {
         Enfiler_FAs ( Q , Fg_As ( N ) ) ;
        
       } ;
       if( Fd_As ( N ) != NULL) {
         Enfiler_FAs ( Q , Fd_As ( N ) ) ;
        
       } ;
      
 } ;
    
    }
 /*-----------------------------------------------------------*/
  void Searchbst (Pointeur_As *R1 , Pointeur_As *R2 , Pointeur_As *R3 , string255 *Mot , Pointeur_As *P)
    {

      /** Corps du module **/
     if( ( (strcmp( Caract ( *Mot , 1 ), "Y") == 0  ) || (strcmp( Caract ( *Mot , 1 ), "Z") == 0  ) || (strcmp( Caract ( *Mot , 1 ), "a") == 0  ) )) {
       printf ( " %s", "Search in BST1...\n" ) ;
       Searchbst1 ( & *R1 , & *Mot , & *P, NULL ) ;
       }
     else
       {
       if( ( (strcmp( Caract ( *Mot , 1 ), "Y") > 0  ) || (strcmp( Caract ( *Mot , 1 ), "Z") > 0  ) || (strcmp( Caract ( *Mot , 1 ), "a") > 0  ) )) {
         printf ( " %s", "Search in BST2...\n" ) ;
         Searchbst2 ( & *R2 , & *Mot , & *P, NULL ) ;
         }
       else
         {
         printf ( " %s", "Search in BST3...\n" ) ;
         Searchbst3 ( & *R3 , & *Mot , & *P, NULL ) ;
        
       } ;
      
     } ;
     printf ( " %s", " " ) ;
     if( *P == NULL) {
       printf ( " %s", "Word does not exist\n" ) ;
       }
     else
       {
       printf ( " %s", "Word exist\n" ) ;
       printf ( " %s", Info_As(*P) ) ;
      
     } ;
    
    }
 
/*-----------------------------------------------------------*/
  void Searchbst1 (Pointeur_As *R , string255 *Word , Pointeur_As *P, int *nodes_visited_ptr)
    {
      /** Variables locales **/
      bool Found;
      Pointeur_As Current_node = *R;

      /** Corps du module **/
     *P = NULL; 
     Found  =  False ;
     while( ( ( Current_node != NULL ) && ( ! Found ) && ( (strcmp( Caract ( *Word , 1 ), "Y") == 0  ) || (strcmp( Caract ( *Word , 1 ), "Z") == 0  ) || (strcmp( Caract ( *Word , 1 ), "a") == 0  ) ) )) {

      if (nodes_visited_ptr != NULL) { (*nodes_visited_ptr)++; }
        if(strcmp( Info_As ( Current_node ), *Word) == 0 ) {
         Found  =  True ;
         *P = Current_node;
         }
       else
         {
         if(strcmp( Info_As ( Current_node ), *Word) > 0 ) {
           Current_node  =  Fg_As ( Current_node ) ;
           }
         else
           {
           Current_node  =  Fd_As ( Current_node ) ;
          
         } ;
        
         } ;
      } ;
    
    }

/*-----------------------------------------------------------*/
  void Searchbst2 (Pointeur_As *R , string255 *Word , Pointeur_As *P, int *nodes_visited_ptr)
    {
      /** Variables locales **/
      bool Found;
      Pointeur_As Current_node = *R;

      /** Corps du module **/
     Found  =  False ;
     *P = NULL;
     while( ( ( Current_node != NULL ) && ( ! Found ) && ( (strcmp( Caract ( *Word , 1 ), "Y") != 0  ) && (strcmp( Caract ( *Word , 1 ), "Z") != 0  ) && (strcmp( Caract ( *Word , 1 ), "a") != 0  ) ) )) {
      if (nodes_visited_ptr != NULL) { (*nodes_visited_ptr)++; }

       if(strcmp( Info_As ( Current_node ), *Word) == 0 ) {
         *P  =  Current_node ;
         Found  =  True ;
         }
       else
         {
         if(strcmp( Info_As ( Current_node ), *Word) > 0 ) {
           Current_node  =  Fg_As ( Current_node ) ;
           }
         else
           {
           Current_node  =  Fd_As ( Current_node ) ;
          
         } ;
        
       } ;
      
 } ;
    
    }

/*-----------------------------------------------------------*/
  void Searchbst3 (Pointeur_As *R , string255 *Word , Pointeur_As *P, int *nodes_visited_ptr)
    {
      /** Variables locales **/
      bool Found;
      Pointeur_As Current_node = *R;

      /** Corps du module **/
     Found  =  False ;
     *P = NULL;
     while( ( ( Current_node != NULL ) && ( ! Found ) && ( (strcmp( Caract ( *Word , 1 ), "Y") != 0  ) && (strcmp( Caract ( *Word , 1 ), "Z") != 0  ) && (strcmp( Caract ( *Word , 1 ), "a") != 0  ) ) )) {
      if (nodes_visited_ptr != NULL) { (*nodes_visited_ptr)++; }

      if(strcmp( Info_As ( Current_node ), *Word) == 0 ) {
         Found  =  True ;
         *P  =  Current_node ;
         }
       else
         {
         if(strcmp( Info_As ( Current_node ), *Word) > 0 ) {
           Current_node  =  Fg_As ( Current_node ) ;
           }
         else
           {
           Current_node  =  Fd_As ( Current_node ) ;
          
         } ;
        
       } ;
      
 } ;
     
    
    }
  void Rangebst (Pointeur_As *R1 , Pointeur_As *R2 , Pointeur_As *R3 , string255 *Mot1 , string255 *Mot2 ) {
      /** Corps du module **/
     if( ( (strcmp( Caract ( *Mot1 , 1 ), "Y") == 0  ) || (strcmp( Caract ( *Mot1 , 1 ), "Z") == 0  ) || (strcmp( Caract ( *Mot1 , 1 ), "a") == 0  ) )) {
       printf ( " %s", "Search in BST1...\n" ) ;
       Rangequery ( & *R1 , & *Mot1 , & *Mot2, NULL ) ;
       }
     else
       {
       if( ( (strcmp( Caract ( *Mot1 , 1 ), "Y") > 0  ) || (strcmp( Caract ( *Mot1 , 1 ), "Z") > 0  ) || (strcmp( Caract ( *Mot1 , 1 ), "a") > 0  ) )) {
         printf ( " %s", "Search in BST2...\n" ) ;
         Rangequery ( & *R2 , & *Mot1 , & *Mot2,NULL ) ;
         }
       else
         {
         printf ( " %s", "Search in BST3...\n" ) ;
         Rangequery ( & *R3 , & *Mot1 , & *Mot2,NULL ) ;
        
       } ;
       printf("\n"); // newline after range query output
      
     } ;
    
    }
  /*-----------------------------------------------------------*/
//  node counting 
  void Rangequery (Pointeur_As *R_ptr , string255 *A_param , string255 *B_param, int *nodes_traversed_ptr) {
    Pointeur_As P_node_iter=NULL; 
    Pointeur_As temp_P_for_next; 
    int smallest_nodes_count = 0;
    int next_inorder_nodes_count = 0;

    if (nodes_traversed_ptr != NULL) { *nodes_traversed_ptr = 0; } 

    Searchsmallest (R_ptr , A_param , &P_node_iter, nodes_traversed_ptr ? &smallest_nodes_count : NULL ) ;
    if (nodes_traversed_ptr) { *nodes_traversed_ptr += smallest_nodes_count; }

    while( P_node_iter != NULL ) {
      if (nodes_traversed_ptr) { (*nodes_traversed_ptr)++; } 
      if(strcmp( Info_As ( P_node_iter ), *B_param) <= 0 ) {
        if (nodes_traversed_ptr == NULL) printf ( " %s\n", Info_As(P_node_iter) ); 
        
        temp_P_for_next = P_node_iter; 
        P_node_iter = Next_inordre (&temp_P_for_next, nodes_traversed_ptr ? &next_inorder_nodes_count : NULL ) ;
        if (nodes_traversed_ptr) { *nodes_traversed_ptr += next_inorder_nodes_count; }

      } else { P_node_iter = NULL; }; 
    } ;
  }
// Next_inordre with node counting
  Pointeur_As Next_inordre (Pointeur_As *P_curr_ptr, int *nodes_accessed_ptr) {
    Pointeur_As Next_inordre_node =NULL; bool Found_successor;
  
    if (nodes_accessed_ptr != NULL) { *nodes_accessed_ptr = 0; }

    if (P_curr_ptr == NULL || *P_curr_ptr == NULL) return NULL;

    Pointeur_As current_P = *P_curr_ptr; 

    if (nodes_accessed_ptr) (*nodes_accessed_ptr)++; 

    if( Fd_As ( current_P ) != NULL) { 
      if (nodes_accessed_ptr) (*nodes_accessed_ptr)++; 
      Next_inordre_node = Fd_As ( current_P ) ; 
      while( Fg_As ( Next_inordre_node ) != NULL ) {
        if (nodes_accessed_ptr) (*nodes_accessed_ptr)++; 
        Next_inordre_node = Fg_As ( Next_inordre_node ) ; 
      } ;
    } else { 
      if (nodes_accessed_ptr) (*nodes_accessed_ptr)++; 
      Found_successor = False ;
      Pointeur_As P_trace_ancestor = current_P; 
      Pointeur_As Parent_of_trace = Pere_As(P_trace_ancestor);
      if (nodes_accessed_ptr && Parent_of_trace) (*nodes_accessed_ptr)++; 

      while( ( Parent_of_trace != NULL ) && ( ! Found_successor ) ) {
        if (nodes_accessed_ptr) (*nodes_accessed_ptr)++; 
        if( Fg_As ( Parent_of_trace ) == P_trace_ancestor) Found_successor = True ;
        else {
          P_trace_ancestor = Parent_of_trace;
          Parent_of_trace = Pere_As ( P_trace_ancestor ) ;
          if (nodes_accessed_ptr && Parent_of_trace) (*nodes_accessed_ptr)++; 
        } ;
      } ;
      Next_inordre_node = Parent_of_trace; 
    } ;
    *P_curr_ptr = Next_inordre_node; 
    return Next_inordre_node ; 
  }
//  Searchsmallest with node counting
  void Searchsmallest (Pointeur_As *R_ptr_param , string255 *Word_param , Pointeur_As *P_out, int *nodes_visited_ptr) {
    Pointeur_As Q_candidate=NULL; 
    Pointeur_As Current_iter; 
    
    *P_out = NULL; 
    if (R_ptr_param == NULL) return;
    Current_iter = *R_ptr_param;


    while( Current_iter != NULL) {
      if (nodes_visited_ptr) { (*nodes_visited_ptr)++; }
      if( (strcmp( Info_As ( Current_iter ), *Word_param) >= 0  )) { 
        Q_candidate = Current_iter ;        
        Current_iter = Fg_As ( Current_iter ) ; 
      } else {
        Current_iter = Fd_As ( Current_iter ) ; 
      } ;
    } ;
    *P_out = Q_candidate ;
  }
// Inorder_traversal 
  void Inorder_traversal (Pointeur_As *R) {
    /** Variables locales **/
    Pointeur_As _Px1=NULL;
    Pointeur_As _Px2=NULL;

    /** Corps du module **/
    if( R != NULL && *R != NULL) {
      _Px1 = Fg_As ( *R ) ; Inorder_traversal ( &_Px1) ;
      printf ( "%s ", Info_As(*R) ) ; 
      _Px2 = Fd_As ( *R ) ; Inorder_traversal ( &_Px2) ;
    } ;
  }
//  File_gen_word
  void File_gen_word() {
    FILE *F_gen; Typestruct1_s S_word_gen ; int I_loop_gen; int N_rand_choice_gen; string255 _Sx_prefix_gen;
    
    S_word_gen = malloc(256 * sizeof(char)); 
    _Sx_prefix_gen = malloc(256 * sizeof(char));
    if (!S_word_gen || !_Sx_prefix_gen) { perror("malloc failed in File_gen_word"); exit(1); }
    
    Ouvrir_s (&F_gen , "F2.z" , "N" ) ;
    if (F_gen == NULL) { 
        printf("Error creating F2.z in File_gen_word\n"); 
        free(S_word_gen); free(_Sx_prefix_gen); return; 
    }
    
    for( I_loop_gen = 1 ;I_loop_gen <=  101 ; ++I_loop_gen){ 
      N_rand_choice_gen = Aleanombre(10) ; 
      char* random_suffix_gen = Aleachaine(Aleanombre(5) + 3 ); 
      if (random_suffix_gen == NULL) { 
          strcpy(random_suffix_gen = "", ""); 
      }

      if( N_rand_choice_gen == 0 ) strcpy (_Sx_prefix_gen, "Y");
      else if( N_rand_choice_gen == 1 ) strcpy (_Sx_prefix_gen, "Z");
      else if( N_rand_choice_gen == 2 ) strcpy (_Sx_prefix_gen, "a");
      else _Sx_prefix_gen[0] = '\0'; 

      if (_Sx_prefix_gen[0] != '\0') { 
          strcpy(S_word_gen, _Sx_prefix_gen); 
          strcat(S_word_gen, random_suffix_gen); 
      } else {
          strcpy(S_word_gen, random_suffix_gen);
      }
      
      Ecrireseq_s ( F_gen , S_word_gen ) ; 
      if (random_suffix_gen) free(random_suffix_gen);
    } ;
    Fermer_s (F_gen) ; 
    free(S_word_gen); free(_Sx_prefix_gen);
  }

// new: File_gen_N_words 
  void File_gen_N_words(const char* filename, int num_words) {
    FILE *F; Typestruct1_s S_word; string255 _Sx_prefix;
    S_word = malloc(256 * sizeof(char)); _Sx_prefix = malloc(256 * sizeof(char));
    if (!S_word || !_Sx_prefix) { perror("malloc failed in File_gen_N_words"); exit(1); }
    
    Ouvrir_s(&F, (char*)filename, "N"); 
    if (F == NULL) { 
        printf("Error creating %s in File_gen_N_words\n",filename); 
        free(S_word);free(_Sx_prefix);return;
    }

    for (int i = 0; i < num_words; ++i) {
        int N_rand_choice = Aleanombre(10); 
        char* random_suffix = Aleachaine(Aleanombre(5) + 3);
        if(random_suffix == NULL) random_suffix = strdup("");


        if (N_rand_choice == 0) strcpy(_Sx_prefix, "Y");
        else if (N_rand_choice == 1) strcpy(_Sx_prefix, "Z");
        else if (N_rand_choice == 2) strcpy(_Sx_prefix, "a");
        else _Sx_prefix[0] = '\0';

        if (_Sx_prefix[0] != '\0') { strcpy(S_word, _Sx_prefix); strcat(S_word, random_suffix); }
        else strcpy(S_word, random_suffix);
        
        Ecrireseq_s(F, S_word); 
        if(random_suffix) free(random_suffix);
    }
    Fermer_s(F); free(S_word); free(_Sx_prefix);
  }

// new : Function Generate_N_Word_Pairs_File
  void Generate_N_Word_Pairs_File(const char* filename, int num_pairs) {
    FILE *F; Typestruct1_s word1_buf, word2_buf;
    word1_buf = malloc(256 * sizeof(char)); word2_buf = malloc(256 * sizeof(char));
    if (!word1_buf || !word2_buf) { perror("malloc failed for word pair buffers"); exit(1); }
    
    Ouvrir_s(&F, (char*)filename, "N");
    if (F == NULL) { 
        printf("Error creating %s\n",filename); 
        free(word1_buf);free(word2_buf);return;
    }
    for (int i = 0; i < num_pairs; ++i) {
        char* w1_temp = Aleachaine(Aleanombre(5) + 3);
        char* w2_temp = Aleachaine(Aleanombre(5) + 3);
        if (!w1_temp) w1_temp = strdup("");
        if (!w2_temp) w2_temp = strdup("");


        if (strcmp(w1_temp, w2_temp) > 0) { 
            char* temp_swap = w1_temp; w1_temp = w2_temp; w2_temp = temp_swap; 
        }
        strcpy(word1_buf, w1_temp); strcpy(word2_buf, w2_temp);
        Ecrireseq_s(F, word1_buf); Ecrireseq_s(F, word2_buf);
        
        if(w1_temp) free(w1_temp); 

        if(w2_temp && w2_temp != w1_temp) free(w2_temp); // if they point to same ""
    }
    Fermer_s(F); free(word1_buf); free(word2_buf);
  }

  void RangeSearch_Triplet_Sim(Pointeur_As R1_in, Pointeur_As R2_in, Pointeur_As R3_in, string255 Mot1_in, string255 Mot2_in, int *nodes_traversed_ptr) {
    if (nodes_traversed_ptr) *nodes_traversed_ptr = 0; 

    char* first_char_mot1 = Caract(Mot1_in, 1);
    if (!first_char_mot1 || first_char_mot1[0] == '\0') { if(first_char_mot1) free(first_char_mot1); return; }

    if( (strcmp(first_char_mot1, "Y") == 0) || (strcmp(first_char_mot1, "Z") == 0) || (strcmp(first_char_mot1, "a") == 0) ) {
      Rangequery(&R1_in, &Mot1_in, &Mot2_in, nodes_traversed_ptr);
    } else if( (strcmp(first_char_mot1, "Y") > 0) && (strcmp(first_char_mot1, "Z") > 0) && (strcmp(first_char_mot1, "a") > 0) ) {
      Rangequery(&R2_in, &Mot1_in, &Mot2_in, nodes_traversed_ptr);
    } else {
      Rangequery(&R3_in, &Mot1_in, &Mot2_in, nodes_traversed_ptr);
    }
    free(first_char_mot1);
  }
// NEw Function Simulate_Single_Word_Search_Efficiency
void Simulate_Single_Word_Search_Efficiency() {
    printf("\n--- Simulation: Single Word Search Efficiency ---\n");
    printf("M_iterations=%d, N_build=%d, N_search=%d\n", SIM_M_ITERATIONS, SIM_N_BUILD_WORDS, SIM_N_SEARCH_WORDS);
    
    long long total_path_bst0_succ = 0, total_path_bst0_unsucc = 0;
    long long total_path_bst1_succ = 0, total_path_bst1_unsucc = 0;
    long long total_path_bst2_succ = 0, total_path_bst2_unsucc = 0;
    long long total_path_bst3_succ = 0, total_path_bst3_unsucc = 0;
    long long count_bst0_succ = 0, count_bst0_unsucc = 0;
    long long count_bst1_succ = 0, count_bst1_unsucc = 0;
    long long count_bst2_succ = 0, count_bst2_unsucc = 0;
    long long count_bst3_succ = 0, count_bst3_unsucc = 0;


    Pointeur_As R0_sim = NULL, R1_sim_s = NULL, R2_sim_s = NULL, R3_sim_s = NULL; 
    Pointeur_As P_found_node = NULL;
    int path_len_curr = 0;
    
    FILE *F_search_src, *F_search_other;
    Typestruct1_s search_word_buf = malloc(256); 
    if(!search_word_buf) {perror("malloc failed for search_word_buf"); exit(1);}

    for (int i = 0; i < SIM_M_ITERATIONS; ++i) {
        printf("Iteration %d/%d...\n", i + 1, SIM_M_ITERATIONS);
        File_gen_N_words("sim_F_build.z", SIM_N_BUILD_WORDS);
        File_gen_N_words("sim_F_search.z", SIM_N_SEARCH_WORDS);

        Destroy_As(&R0_sim); Destroy_As(&R1_sim_s); Destroy_As(&R2_sim_s); Destroy_As(&R3_sim_s);
        R0_sim = NULL; R1_sim_s = NULL; R2_sim_s = NULL; R3_sim_s = NULL; // clear previous tree, to not mess current simulation

        Createbst0(&R0_sim, "sim_F_build.z");
        Createbst1(&R1_sim_s, "sim_F_build.z");
        Createbst2(&R2_sim_s, "sim_F_build.z");
        Createbst3(&R3_sim_s, "sim_F_build.z");

        Ouvrir_s(&F_search_src, "sim_F_build.z", "A");
        if (F_search_src) {
            search_word_buf[0] = '\0';
            Lireseq_s(F_search_src, search_word_buf);
            while (!Finfich_s(F_search_src) && search_word_buf[0] != '\0') {
                path_len_curr = 0; 
                Search(&R0_sim, &search_word_buf, &P_found_node, &path_len_curr);
                if (P_found_node) { total_path_bst0_succ += path_len_curr; count_bst0_succ++; }
                
                path_len_curr = 0; 

                char* first_char = Caract(search_word_buf, 1);
                P_found_node = NULL;

                if (!first_char || first_char[0] == '\0') { if(first_char) free(first_char); return; } 

                if( (strcmp(first_char, "Y") == 0) || (strcmp(first_char, "Z") == 0) || (strcmp(first_char, "a") == 0) ) {
                  path_len_curr = 0;
                  Searchbst1 (&R1_sim_s, &search_word_buf, &P_found_node, &path_len_curr); 
                  if (P_found_node) { total_path_bst1_succ += path_len_curr; count_bst1_succ++; }
                } else if( (strcmp(first_char, "Y") > 0) && (strcmp(first_char, "Z") > 0) && (strcmp(first_char, "a") > 0) ) {
                  path_len_curr = 0;
                  Searchbst2 (&R2_sim_s, &search_word_buf, &P_found_node, &path_len_curr); 
                  if (P_found_node) { total_path_bst2_succ += path_len_curr; count_bst2_succ++; }
                } else {
                  path_len_curr = 0;
                  Searchbst3 (&R3_sim_s, &search_word_buf, &P_found_node, &path_len_curr);
                  if (P_found_node) { total_path_bst3_succ += path_len_curr; count_bst3_succ++; } 
                }
                
                search_word_buf[0] = '\0'; 
                Lireseq_s(F_search_src, search_word_buf);
            } 
            Fermer_s(F_search_src);
        }

        Ouvrir_s(&F_search_other, "sim_F_search.z", "A");
         if (F_search_other) {
            search_word_buf[0] = '\0'; Lireseq_s(F_search_other, search_word_buf);
            while (!Finfich_s(F_search_other) && search_word_buf[0] != '\0') {
                path_len_curr = 0; Search(&R0_sim, &search_word_buf, &P_found_node, &path_len_curr);
                if (P_found_node) { total_path_bst0_succ += path_len_curr; count_bst0_succ++; }
                else { total_path_bst0_unsucc += path_len_curr; count_bst0_unsucc++; }


                path_len_curr = 0; 

                char* first_char = Caract(search_word_buf, 1);
                P_found_node = NULL;

                if (!first_char || first_char[0] == '\0') { if(first_char) free(first_char); return; } 

                if( (strcmp(first_char, "Y") == 0) || (strcmp(first_char, "Z") == 0) || (strcmp(first_char, "a") == 0) ) {
                  path_len_curr = 0;
                  Searchbst1 (&R1_sim_s, &search_word_buf, &P_found_node, &path_len_curr); 
                  if (P_found_node) { total_path_bst1_succ += path_len_curr; count_bst1_succ++; }
                  else { total_path_bst1_unsucc+= path_len_curr; count_bst1_unsucc++; }
                } else if( (strcmp(first_char, "Y") > 0) && (strcmp(first_char, "Z") > 0) && (strcmp(first_char, "a") > 0) ) {
                  path_len_curr = 0; 
                  Searchbst2 (&R2_sim_s, &search_word_buf, &P_found_node, &path_len_curr); 
                  if (P_found_node) { total_path_bst2_succ += path_len_curr; count_bst2_succ++; }
                  else { total_path_bst2_unsucc+= path_len_curr; count_bst2_unsucc++; }
                } else {
                  path_len_curr = 0;
                  Searchbst3 (&R3_sim_s, &search_word_buf, &P_found_node, &path_len_curr);
                  if (P_found_node) { total_path_bst3_succ += path_len_curr; count_bst3_succ++; }
                  else { total_path_bst3_unsucc+= path_len_curr; count_bst3_unsucc++; } 
                }

                search_word_buf[0] = '\0'; Lireseq_s(F_search_other, search_word_buf);
            } Fermer_s(F_search_other);
        }
    }
    Destroy_As(&R0_sim); Destroy_As(&R1_sim_s); Destroy_As(&R2_sim_s); Destroy_As(&R3_sim_s);
    free(search_word_buf);

    printf("\n---  Results (Single Word Search Path Length) ---\n");
    printf("TreeType,SearchOutcome,TotalPathLength,TotalSearches,AvgPathLength\n");
    if (count_bst0_succ > 0) printf("BST0,Successful,%lld,%lld,%.2f\n", total_path_bst0_succ, count_bst0_succ, (double)total_path_bst0_succ / count_bst0_succ);
    else printf("BST0,Successful,0,0,0.00\n");
    if (count_bst0_unsucc > 0) printf("BST0,Unsuccessful,%lld,%lld,%.2f\n", total_path_bst0_unsucc, count_bst0_unsucc, (double)total_path_bst0_unsucc / count_bst0_unsucc);
    else printf("BST0,Unsuccessful,0,0,0.00\n");
    if (count_bst1_succ > 0) printf("BST1,Successful,%lld,%lld,%.2f\n", total_path_bst1_succ, count_bst1_succ, (double)total_path_bst1_succ / count_bst1_succ);
    else printf("BST1,Successful,0,0,0.00\n");
    if (count_bst1_unsucc > 0) printf("BST1,Unsuccessful,%lld,%lld,%.2f\n", total_path_bst1_unsucc, count_bst1_unsucc, (double)total_path_bst1_unsucc / count_bst1_unsucc);
    else printf("BST1,Unsuccessful,0,0,0.00\n");
    if (count_bst2_succ > 0) printf("BST2,Successful,%lld,%lld,%.2f\n", total_path_bst2_succ, count_bst2_succ, (double)total_path_bst2_succ / count_bst2_succ);
    else printf("BST2,Successful,0,0,0.00\n");
    if (count_bst2_unsucc > 0) printf("BST2,Unsuccessful,%lld,%lld,%.2f\n", total_path_bst2_unsucc, count_bst2_unsucc, (double)total_path_bst2_unsucc / count_bst2_unsucc);
    else printf("BST2,Unsuccessful,0,0,0.00\n");
    if (count_bst3_succ > 0) printf("BST3,Successful,%lld,%lld,%.2f\n", total_path_bst3_succ, count_bst3_succ, (double)total_path_bst3_succ / count_bst3_succ);
    else printf("BST3,Successful,0,0,0.00\n");
    if (count_bst3_unsucc > 0) printf("BST3,Unsuccessful,%lld,%lld,%.2f\n", total_path_bst3_unsucc, count_bst3_unsucc, (double)total_path_bst3_unsucc / count_bst3_unsucc);
    else printf("BST3,Unsuccessful,0,0,0.00\n");

    printf("Triplet,Successful,%lld,%lld,%.2f\n", (total_path_bst1_succ+total_path_bst2_succ+total_path_bst3_succ), (count_bst1_succ+count_bst2_succ+count_bst3_succ), (double)(total_path_bst1_succ+total_path_bst2_succ+total_path_bst3_succ) / (count_bst1_succ+count_bst2_succ+count_bst3_succ));
    printf("Triplet,Unsuccessful,%lld,%lld,%.2f\n", (total_path_bst1_unsucc+total_path_bst2_unsucc+total_path_bst3_unsucc), (count_bst1_unsucc+count_bst2_unsucc+count_bst3_unsucc), (double)(total_path_bst1_unsucc+total_path_bst2_unsucc+total_path_bst3_unsucc) / (count_bst1_unsucc+count_bst2_unsucc+count_bst3_unsucc));

    
}

// NEW: Function Simulate_Range_Search_Efficiency
void Simulate_Range_Search_Efficiency() {
    printf("\n--- Simulation: Range Search Efficiency (Total Nodes Traversed) ---\n");
    printf("M_iterations=%d, N_build=%d, N_pairs=%d\n", SIM_M_ITERATIONS, SIM_N_BUILD_WORDS, SIM_N_RANGE_PAIRS);

    long long total_nodes_bst0_range = 0;
    long long total_nodes_triplet_range = 0;
    long long count_range_queries = 0;

    Pointeur_As R0_sim_range = NULL, R1_sim_range = NULL, R2_sim_range = NULL, R3_sim_range = NULL;
    int nodes_traversed_curr = 0;
    
    FILE *F_pairs;
    Typestruct1_s word1_pair_buf = malloc(256); Typestruct1_s word2_pair_buf = malloc(256);
    if(!word1_pair_buf || !word2_pair_buf) {perror("malloc failed for pair_bufs"); exit(1);}

    for (int i = 0; i < SIM_M_ITERATIONS; ++i) {
        printf("Iteration %d/%d...\n", i + 1, SIM_M_ITERATIONS);
        File_gen_N_words("sim_F_build_range.z", SIM_N_BUILD_WORDS);
        Generate_N_Word_Pairs_File("sim_F_pairs.z", SIM_N_RANGE_PAIRS);

        Destroy_As(&R0_sim_range); Destroy_As(&R1_sim_range); Destroy_As(&R2_sim_range); Destroy_As(&R3_sim_range);
        R0_sim_range = NULL; R1_sim_range = NULL; R2_sim_range = NULL; R3_sim_range = NULL;

        Createbst0(&R0_sim_range, "sim_F_build_range.z");
        Createbst1(&R1_sim_range, "sim_F_build_range.z");
        Createbst2(&R2_sim_range, "sim_F_build_range.z");
        Createbst3(&R3_sim_range, "sim_F_build_range.z");

        Ouvrir_s(&F_pairs, "sim_F_pairs.z", "A");
        if (F_pairs) {
            word1_pair_buf[0] = '\0'; Lireseq_s(F_pairs, word1_pair_buf);
            word2_pair_buf[0] = '\0'; Lireseq_s(F_pairs, word2_pair_buf); // Read second part of pair
            while (!Finfich_s(F_pairs) && word1_pair_buf[0] != '\0' && word2_pair_buf[0] != '\0') {
                nodes_traversed_curr = 0; Rangequery(&R0_sim_range, &word1_pair_buf, &word2_pair_buf, &nodes_traversed_curr);
                total_nodes_bst0_range += nodes_traversed_curr;

                nodes_traversed_curr = 0; RangeSearch_Triplet_Sim(R1_sim_range, R2_sim_range, R3_sim_range, word1_pair_buf, word2_pair_buf, &nodes_traversed_curr);
                total_nodes_triplet_range += nodes_traversed_curr;
                
                count_range_queries++;
                word1_pair_buf[0] = '\0'; Lireseq_s(F_pairs, word1_pair_buf);
                word2_pair_buf[0] = '\0'; Lireseq_s(F_pairs, word2_pair_buf);
            } Fermer_s(F_pairs);
        }
    }
    Destroy_As(&R0_sim_range); Destroy_As(&R1_sim_range); Destroy_As(&R2_sim_range); Destroy_As(&R3_sim_range);
    free(word1_pair_buf); free(word2_pair_buf);

    printf("\n--- Aggregated Results (Range Search Nodes Traversed) ---\n");
    printf("TreeType,TotalNodesTraversed,TotalQueries,AvgNodesPerQuery\n");
    if (count_range_queries > 0) {
        printf("BST0,%lld,%lld,%.2f\n", total_nodes_bst0_range, count_range_queries, (double)total_nodes_bst0_range / count_range_queries);
        printf("Triplet,%lld,%lld,%.2f\n", total_nodes_triplet_range, count_range_queries, (double)total_nodes_triplet_range / count_range_queries);
    } else {
        printf("BST0,0,0,0.00\n");
        printf("Triplet,0,0,0.00\n");
    }
}


//  Menu (fixed bug and added simulation options)
  void Menu() {
    int Mainchoice = 0; int Choice1 = 0; int Choix_submenu = 0; int Choice2 = 0; int scanf_status;
    // Global variables 

   while( Mainchoice != 5) { 
     printf ( "\n____________PRINCIPLE MENU____________\n" ) ; 
     printf ( " 1. Part I : Initial Tree Construction & Verification (uses F2.z)\n" ) ; 
     printf ( " 2. Part II : Word Search Operations (uses trees from option 1)\n" ) ; 
     printf ( " 3. Simulation: Single Word Search Efficiency\n" ) ; 
     printf ( " 4. Simulation: Range Search Efficiency\n" ) ;
     printf ( " 5. Quitter\n" ) ; 
     printf( " Your choice: "); 
     scanf_status = scanf ( " %d", &Mainchoice );
     while(getchar() != '\n'); 

     if (scanf_status != 1) { printf("Invalid input. Please enter a number.\n"); Mainchoice = 0; continue; }

     if( Mainchoice == 1) {
       Choice1 = 0;
       while( Choice1 != 4) {
         puts(""); printf ( " ______Initial Tree Construction & Verification (F2.z)______\n" ) ; 
         printf ( " 1. Generate file F2.z (N=20 words default).\n" ) ; 
         printf ( " 2. Construct BST1, BST2, and BST3 from F2.z.\n" ) ; 
         printf ( " 3. Perform operations on BSTs (from F2.z):\n" ) ; 
         printf ( " 4. Back to main menu.\n" ) ; puts(""); printf( " Your choice: "); 
         scanf_status = scanf ( " %d", &Choice1 ); while(getchar() != '\n');
         if (scanf_status != 1) { printf("Invalid input.\n"); Choice1 = 0; continue; }

         if( Choice1 == 1) { File_gen_word(); printf ( " Done (F2.z generated).\n" ); } 
         else if( Choice1 == 2) { 
           Destroy_As(&R1); Destroy_As(&R2); Destroy_As(&R3); 
           R1 = NULL; R2 = NULL; R3 = NULL; //NULL after destroy
           Createbst1 (&R1, "F2.z"); Createbst2 (&R2, "F2.z"); Createbst3 (&R3, "F2.z");
           printf ( " Done (BSTs built from F2.z).\n" ); 
         } 
         else if( Choice1 == 3) { 
            Choix_submenu = 0;
            while( Choix_submenu != 5) {
                puts(""); printf ( " ______Operations sur les arbres (BSTs from F2.z)______\n" ) ; 
                printf ( " 1. Count Y,Z,a words.\n" ); printf ( " 2. Compute depth.\n" ) ;
                printf ( " 3. Inorder traversal.\n" ); printf ( " 4. Y,Z,a count per level.\n" ) ;
                printf ( " 5. Back.\n" ); puts(""); printf( " Your choice: ");
                scanf_status = scanf(" %d", &Choix_submenu); while(getchar()!='\n');
                if(scanf_status!=1){printf("Invalid input.\n"); Choix_submenu=0; continue;}

                if(Choix_submenu==1){ printf("\nBST1:");Count(&R1); printf("BST2:");Count(&R2); printf("BST3:");Count(&R3); }
                else if(Choix_submenu==2){ printf("\nDepth BST1:%d\nDepth BST2:%d\nDepth BST3:%d\n", Depth(&R1),Depth(&R2),Depth(&R3)); }
                else if(Choix_submenu==3){ 
                    printf("\nBST1 Inorder:");Inorder_traversal(&R1);printf("\n");
                    printf("BST2 Inorder:");Inorder_traversal(&R2);printf("\n");
                    printf("BST3 Inorder:");Inorder_traversal(&R3);printf("\n");
                }
                else if(Choix_submenu==4){ 
                    printf("\nBST1 Level Y,Z,a Count:\n");Levelcount(&R1);
                    printf("BST2 Level Y,Z,a Count:\n");Levelcount(&R2);
                    printf("BST3 Level Y,Z,a Count:\n");Levelcount(&R3);
                }
                else if(Choix_submenu!=5) printf("Invalid choice.\n");
            }
         }
         else if (Choice1 != 4) printf("Invalid choice.\n");
       } 
     } 
     else if( Mainchoice == 2) { 
        Choice2 = 0;
        while( Choice2 != 3) {
            puts(""); printf ( " ______Word Search Operations (uses BSTs from F2.z)______\n" ) ;
            printf ( " 1. Single Word Search.\n" ); printf ( " 2. Range Search.\n" );
            printf ( " 3. Back.\n" ); puts(""); printf( " Your choice: ");
            scanf_status = scanf(" %d", &Choice2); while(getchar()!='\n');
            if(scanf_status!=1){printf("Invalid input.\n");Choice2=0;continue;}

            if(Choice2==1){
                printf("\nEnter Word to search: "); scanf(" %255[^\n]", Word); while(getchar()!='\n');
                Searchbst(&R1, &R2, &R3, &Word, &P); 
            } else if(Choice2==2){
                printf("\nEnter Word1: "); scanf(" %255[^\n]", Mot1); while(getchar()!='\n');
                printf("Enter Word2: "); scanf(" %255[^\n]", Mot2); while(getchar()!='\n');
                if (strcmp(Mot1, Mot2) > 0) { //  Mot1 <= Mot2 for range query
                    string255 temp = Mot1; Mot1 = Mot2; Mot2 = temp;
                    printf("Note: Word1 and Word2 swapped for correct range [min, max].\n");
                }
                Rangebst(&R1, &R2, &R3, &Mot1, &Mot2 );
            } else if(Choice2!=3) printf("Invalid choice.\n");
        }
     } 
     else if (Mainchoice == 3) { Simulate_Single_Word_Search_Efficiency(); }
     else if (Mainchoice == 4) { Simulate_Range_Search_Efficiency(); }
     else if (Mainchoice != 5 && Mainchoice !=0 ) printf("Invalid choice. Please enter 1-5.\n");
   } 
   printf("Exiting program.\n");
   //free
   Destroy_As(&R); 
   Destroy_As(&R1); 
   Destroy_As(&R2); 
   Destroy_As(&R3); 
  }

// main 
  int main(int argc, char *argv[]) {
     srand(time(NULL));
     // globall
     Word = malloc(256 * sizeof(char)); 
     Mot1 = malloc(256 * sizeof(char)); 
     Mot2 = malloc(256 * sizeof(char));
     if (!Word || !Mot1 || !Mot2) { 
         perror("Failed to allocate global strings in main"); 
         return 1; 
     }
     
     Menu() ;
     
     // Free
     free(Word); Word = NULL;
     free(Mot1); Mot1 = NULL;
     free(Mot2); Mot2 = NULL;
     

     printf("Press Enter to continue..."); 
     getchar(); 
     return 0;
  };
