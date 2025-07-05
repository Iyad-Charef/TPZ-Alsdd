
  /*-------------------------------------------------------------------------*/
  /*                 TP 2 Khawarizm : Optimized Word Search                  */
  /*                           Réalisé par :                                 */
  /*                           Charef Iyad                                   */
  /*                   Section : D       Groupe : 13                         */
  /*-------------------------------------------------------------------------*/
   SOIENT
       H UN ENTIER ;
       R , R1 , R2 , R3 , P DES ARB DE CHAINE ;
       Word , Mot1 , Mot2 DES CHAINES ;
       Search UNE ACTION ;
       File_gen_word UNE ACTION ;
       Insertbst UNE ACTION ;
       Createbst UNE ACTION ;
       Createbst1 UNE ACTION ;
       Createbst2 UNE ACTION ;
       Createbst3 UNE ACTION ;
       Count UNE ACTION ;
       Depth UNE FONCTION ( ENTIER ) ;
       Inorder_traversal UNE ACTION ;
       Levelcount UNE ACTION ;
       Searchbst UNE ACTION ;
       Rangebst UNE ACTION ;
       Rangequery UNE ACTION ;
       Next_inordre UNE FONCTION ( ARB DE CHAINE ) ;
       Searchsmallest UNE ACTION ;
       Searchbst1 UNE ACTION ;
       Searchbst3 UNE ACTION ;
       Levelbylevel UNE ACTION ;
       Menu UNE ACTION ;
       Ror UNE FONCTION ( ARB DE CHAINE ) ;
       Rol UNE FONCTION ( ARB DE CHAINE ) ;
       Nodelevel UNE FONCTION ( ENTIER ) ;
      
   DEBUT
       APPEL Menu ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Insertbst ( Mot , R , Done )
   SOIENT
       R , P UN ARB DE CHAINES ;
       Mot UNE CHAINE ;
       Done UN BOOLEEN ;
      
   DEBUT
       Done := FAUX ;
       SI ( R = NIL )
           CREERNOEUD ( R ) ;
           AFF_INFO ( R , Mot ) ;
           AFF_PERE ( R , NIL ) ;
           Done := VRAI ;
          
       SINON
           SI ( INFO ( R ) = Mot )
               Done := VRAI ;
              
           SINON
               SI ( INFO ( R ) > Mot )
                   P := FG ( R ) ;
                   APPEL Insertbst ( Mot , P , Done ) ;
                   AFF_FG ( R , P ) ;
                   AFF_PERE ( P , R ) ;
                  
               SINON
                   P := FD ( R ) ;
                   APPEL Insertbst ( Mot , P , Done ) ;
                   AFF_FD ( R , P ) ;
                   AFF_PERE ( P , R ) ;
                  
               FSI ;
              
           FSI ;
          
       FSI ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Createbst ( R )
  /*bst0*/
   SOIENT
       N , A DES ENTIERS ;
       R UN ARB DE CHAINE ;
       F UN FICHIER DE CHAINE BUFFER S ;
       Done UN BOOLEEN ;
      
   DEBUT
       OUVRIR ( F , 'F2.z' , 'A' ) ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           APPEL Insertbst ( S , R , Done ) ;
          
       FTQ ;
       FERMER ( F ) ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Createbst1 ( R )
   SOIENT
       N , A DES ENTIERS ;
       R , P , Q DES ARB DE CHAINE ;
       F UN FICHIER DE CHAINE BUFFER S ;
       Done UN BOOLEEN ;
      
   DEBUT
       OUVRIR ( F , 'F2.z' , 'A' ) ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           APPEL Insertbst ( S , R , Done ) ;
           APPEL Search ( R , S , P ) ;
           SI ( ( CARACT ( S , 1 ) = 'Y' ) OU ( CARACT ( S , 1 ) = 'Z' ) OU ( CARACT ( S , 1 ) = 'a' ) )
               TQ ( ( PERE ( P ) <> NIL ) )
                   Q := PERE ( P ) ;
                   SI ( P = FG ( PERE ( P ) ) )
                       P := Ror ( P ) ;
                      
                   SINON
                       P := Rol ( P ) ;
                      
                   FSI ;
                   SI ( Q = R )
                       R := P ;
                      
                   FSI ;
                  
               FTQ ;
              
           FSI ;
          
       FTQ ;
       FERMER ( F ) ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Createbst2 ( R )
   SOIENT
       N , A , L , Cpt DES ENTIERS ;
       R , P , Q DES ARB DE CHAINE ;
       F UN FICHIER DE CHAINE BUFFER S ;
       Done UN BOOLEEN ;
      
   DEBUT
       OUVRIR ( F , 'F2.z' , 'A' ) ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           APPEL Insertbst ( S , R , Done ) ;
           APPEL Search ( R , S , P ) ;
           SI ( ( CARACT ( S , 1 ) = 'Y' ) OU ( CARACT ( S , 1 ) = 'Z' ) OU ( CARACT ( S , 1 ) = 'a' ) )
               L := Nodelevel ( R , P ) ;
               L := L / 2 ;
               Cpt := 0 ;
               TQ ( ( PERE ( P ) <> NIL ) ET ( Cpt < L ) )
                   Q := PERE ( P ) ;
                   SI ( P = FG ( PERE ( P ) ) )
                       P := Ror ( P ) ;
                      
                   SINON
                       P := Rol ( P ) ;
                      
                   FSI ;
                   SI ( Q = R )
                       R := P ;
                      
                   FSI ;
                   Cpt := Cpt + 1
               FTQ ;
              
           FSI ;
          
       FTQ ;
       FERMER ( F ) ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Createbst3 ( R )
   SOIENT
       N , A DES ENTIERS ;
       R , P , Q DES ARB DE CHAINE ;
       F UN FICHIER DE CHAINE BUFFER S ;
       Done UN BOOLEEN ;
      
   DEBUT
       OUVRIR ( F , 'F2.z' , 'A' ) ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           APPEL Insertbst ( S , R , Done ) ;
           APPEL Search ( R , S , P ) ;
           SI ( ( CARACT ( S , 1 ) < 'Y' ) OU ( CARACT ( S , 1 ) > 'a' ) )
               TQ ( ( P <> NIL ) ET ( PERE ( P ) <> NIL ) )
                   Q := PERE ( P ) ;
                   SI ( P = FG ( PERE ( P ) ) )
                  /* Q */
                       P := Ror ( P ) ;
                      
                   SINON
                       P := Rol ( P ) ;
                      
                   FSI ;
                   SI ( Q = R )
                       R := P ;
                      
                   FSI ;
                  
               FTQ ;
              
           FSI ;
          
       FTQ ;
       FERMER ( F ) ;
      
   FIN
  /*-----------------------------------------------------------*/
   FONCTION Ror ( R ) : ARB DE CHAINE
   SOIENT
       R , A DES ARB DE CHAINE ;
      
   DEBUT
       A := PERE ( R ) ;
       R := FG ( A ) ;
       SI ( R = NIL )
           Ror := A ;
          
       SINON
           AFF_FG ( A , FD ( R ) ) ;
           SI FD ( R ) <> NIL
               AFF_PERE ( FD ( R ) , A ) ;
              
           FSI ;
           AFF_FD ( R , A ) ;
           AFF_PERE ( R , PERE ( A ) ) ;
           SI ( PERE ( A ) <> NIL )
               SI ( FG ( PERE ( A ) ) = A )
                   AFF_FG ( PERE ( A ) , R ) ;
                  
               SINON
                   AFF_FD ( PERE ( A ) , R ) ;
                  
               FSI ;
              
           SINON
               AFF_PERE ( R , NIL ) ;
              
           FSI ;
           AFF_PERE ( A , R ) ;
           Ror := R ;
          
       FSI ;
      
   FIN
  /*-----------------------------------------------------------*/
   FONCTION Rol ( R ) : ARB DE CHAINE
   SOIENT
       R , A DES ARB DE CHAINE ;
      
   DEBUT
       A := PERE ( R ) ;
       R := FD ( A ) ;
       SI ( R = NIL )
           Rol := R ;
          
       SINON
           AFF_FD ( A , FG ( R ) ) ;
           SI FG ( R ) <> NIL
               AFF_PERE ( FG ( R ) , A ) ;
              
           FSI ;
           AFF_FG ( R , A ) ;
           AFF_PERE ( R , PERE ( A ) ) ;
           SI ( PERE ( A ) <> NIL )
               SI ( FG ( PERE ( A ) ) = A )
                   AFF_FG ( PERE ( A ) , R ) ;
                  
               SINON
                   AFF_FD ( PERE ( A ) , R ) ;
                  
               FSI ;
              
           SINON
               AFF_PERE ( R , NIL ) ;
              
           FSI ;
           AFF_PERE ( A , R ) ;
           Rol := R ;
          
       FSI ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Search ( R , Word , P )
  /*node level*/
   SOIENT
       R , P DES ARB DE CHAINE ;
       Word UNE CHAINE ;
      
   DEBUT
       SI ( R = NIL )
           P := NIL ;
          
       SINON
           SI INFO ( R ) = Word
               P := R ;
              
           SINON
               SI INFO ( R ) > Word
                   APPEL Search ( FG ( R ) , Word , P ) ;
                  
               SINON
                   APPEL Search ( FD ( R ) , Word , P ) ;
                  
               FSI ;
              
           FSI ;
          
       FSI ;
      
   FIN
  /*-----------------------------------------------------------*/
   FONCTION Depth ( R ) : ENTIER
   SOIENT
       R UN ARB DE CHAINE ;
       Left , Right DES ENTIERS ;
      
   DEBUT
       SI ( R = NIL )
           Depth := - 1 ;
          
       SINON
           Left := Depth ( FG ( R ) ) ;
           Right := Depth ( FD ( R ) ) ;
           Depth := MAX ( Left , Right ) + 1 ;
          
       FSI ;
      
   FIN
  /*--------------------------------------------------------------*/
   ACTION Count ( R )
  /*Count the number of words starting with X, Y, and Z and Display it*/
   SOIENT
       R , N DES ARB DE CHAINE ;
       Q UNE FILE DE ARB DE CHAINE ;
       Cpt UN ENTIER ;
      
   DEBUT
       Cpt := 0 ;
       CREERFILE ( Q ) ;
       SI ( R <> NIL )
           ENFILER ( Q , R ) ;
          
       FSI ;
       TQ NON FILEVIDE ( Q )
           DEFILER ( Q , N ) ;
           SI ( ( CARACT ( INFO ( N ) , 1 ) = 'Y' ) OU ( CARACT ( INFO ( N ) , 1 ) = 'Z' ) OU ( CARACT ( INFO ( N ) ,
           1 ) = 'a' ) )
               Cpt := Cpt + 1 ;
              
           FSI ;
           SI FG ( N ) <> NIL
               ENFILER ( Q , FG ( N ) ) ;
              
           FSI ;
           SI FD ( N ) <> NIL
               ENFILER ( Q , FD ( N ) ) ;
              
           FSI ;
          
       FTQ ;
       ECRIRE ( 'The number of words starting with X, Y, and Z:' , Cpt )
   FIN
  /*-------------------------------------------------------------*/
   ACTION Levelcount ( R )
   SOIENT
       R , N DES ARB DE CHAINE ;
       Q UNE FILE DE ARB DE CHAINE ;
       Cpt , Level DES ENTIER ;
       C UNE CHAINE ;
      
   DEBUT
       Cpt := 0 ;
       Level := - 1 ;
       CREERFILE ( Q ) ;
       SI ( R <> NIL )
           ENFILER ( Q , R ) ;
          
       FSI ;
       TQ NON FILEVIDE ( Q )
           DEFILER ( Q , N ) ;
           C := INFO ( N ) ;
           SI ( Nodelevel ( R , N ) > Level )
               SI ( Level >= 0 )
                   ECRIRE ( 'Level' , Level ) ;
                   ECRIRE ( 'The number of words starting with X, Y, and Z:' , Cpt ) ;
                   ECRIRE ( '---------------------------------------------------------' ) ;
                  
               FSI ;
               Cpt := 0 ;
               Level := Nodelevel ( R , N ) ;
              
           FSI ;
           SI ( ( CARACT ( C , 1 ) = 'Y' ) OU ( CARACT ( C , 1 ) = 'Z' ) OU ( CARACT ( C , 1 ) = 'a' ) )
          {ECRIRE (INFO(N)); }
               Cpt := Cpt + 1 ;
              
           FSI ;
           SI FG ( N ) <> NIL
               ENFILER ( Q , FG ( N ) ) ;
              
           FSI ;
           SI FD ( N ) <> NIL
               ENFILER ( Q , FD ( N ) ) ;
              
           FSI ;
          
       FTQ ;
       SI ( Level >= 0 )
           ECRIRE ( 'Level' , Level ) ;
           ECRIRE ( 'The number of words starting with X, Y, and Z:' , Cpt ) ;
          
       FSI ;
      
   FIN
  /*-------------------------------------------------------------*/
   FONCTION Nodelevel ( R , P ) : ENTIER ;
  /* Fonction qui calcule le niveau d'un noeud P dans l'arbre de racine R */
   SOIENT
       R , P , Q DES ARB DE CHAINE ;
       Found UN BOOLEEN ;
       Level UN ENTIER ;
      
   DEBUT
       Level := - 1 ;
       Found := FAUX ;
       Q := R ;
       TQ ( ( Q <> NIL ) ET ( NON Found ) )
           Level := Level + 1 ;
           SI ( INFO ( Q ) = INFO ( P ) )
               Found := VRAI ;
              
           SINON
               SI ( INFO ( Q ) < INFO ( P ) )
                   Q := FD ( Q ) ;
                  
               SINON
                   Q := FG ( Q ) ;
                  
               FSI ;
              
           FSI ;
          
       FTQ ;
       Nodelevel := Level ;
      
   FIN
  /*-----------------------------------------------------------------*/
   ACTION Levelbylevel ( R )
   SOIENT
       R , N DES ARB DE CHAINE ;
       Q UNE FILE DE ARB DE CHAINE ;
      
   DEBUT
       CREERFILE ( Q ) ;
       SI ( R <> NIL )
           ENFILER ( Q , R ) ;
          
       FSI ;
       TQ NON FILEVIDE ( Q )
           DEFILER ( Q , N ) ;
           ECRIRE ( INFO ( N ) ) ;
           SI FG ( N ) <> NIL
               ENFILER ( Q , FG ( N ) ) ;
              
           FSI ;
           SI FD ( N ) <> NIL
               ENFILER ( Q , FD ( N ) ) ;
              
           FSI ;
          
       FTQ ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Searchbst ( R1 , R2 , R3 , Mot , P )
   SOIENT
       R1 , R2 , R3 , P DES ARB DE CHAINE ;
       Mot UNE CHAINE ;
      
   DEBUT
       SI ( ( CARACT ( Mot , 1 ) = 'Y' ) OU ( CARACT ( Mot , 1 ) = 'Z' ) OU ( CARACT ( Mot , 1 ) = 'a' ) )
           ECRIRE ( '-----Search in BST1-----' ) ;
           APPEL Searchbst1 ( R1 , Mot , P ) ;
          
       SINON
           SI ( ( CARACT ( Mot , 1 ) > 'Y' ) OU ( CARACT ( Mot , 1 ) > 'Z' ) OU ( CARACT ( Mot , 1 ) > 'a' ) )
               ECRIRE ( '-----Search in BST2-----' ) ;
               APPEL Search ( R2 , Mot , P ) ;
              
           SINON
               ECRIRE ( '-----Search in BST3-----' ) ;
               APPEL Searchbst3 ( R3 , Mot , P ) ;
              
           FSI ;
          
       FSI ;
       SI P = NIL
           ECRIRE ( 'Word does not exist' ) ;
          
       SINON
           ECRIRE ( 'Word exist' ) ;
           ECRIRE ( INFO ( P ) ) ;
          
       FSI ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Searchbst1 ( R , Word , P )
   SOIENT
       R , P DES ARB DE CHAINE ;
       Word UNE CHAINE ;
       Found UN BOOLEEN ;
      
   DEBUT
       Found := FAUX ;
       TQ ( ( R <> NIL ) ET ( NON Found ) ET ( ( CARACT ( Word , 1 ) = 'Y' ) OU ( CARACT ( Word , 1 ) = 'Z' ) OU (
       CARACT ( Word , 1 ) = 'a' ) ) )
           SI INFO ( R ) = Word
               Found := VRAI ;
              
           SINON
               SI INFO ( R ) > Word
                   R := FG ( R ) ;
                  
               SINON
                   R := FD ( R ) ;
                  
               FSI ;
              
           FSI ;
          
       FTQ ;
       P := R ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Searchbst3 ( R , Word , P )
   SOIENT
       R , P DES ARB DE CHAINE ;
       Word UNE CHAINE ;
       Found UN BOOLEEN ;
      
   DEBUT
       Found := FAUX ;
       TQ ( ( R <> NIL ) ET ( NON Found ) ET ( ( CARACT ( Word , 1 ) <> 'Y' ) ET ( CARACT ( Word , 1 ) <> 'Z' ) ET (
       CARACT ( Word , 1 ) <> 'a' ) ) )
           SI INFO ( R ) = Word
               Found := VRAI ;
              
           SINON
               SI INFO ( R ) > Word
                   R := FG ( R ) ;
                  
               SINON
                   R := FD ( R ) ;
                  
               FSI ;
              
           FSI ;
          
       FTQ ;
       P := R ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Rangebst ( R1 , R2 , R3 , Mot1 , Mot2 )
  /*optimized*/
   SOIENT
       R1 , R2 , R3 DES ARB DE CHAINE ;
       Mot1 , Mot2 DES CHAINES ;
      
   DEBUT
       SI ( ( CARACT ( Mot1 , 1 ) = 'Y' ) OU ( CARACT ( Mot1 , 1 ) = 'Z' ) OU ( CARACT ( Mot1 , 1 ) = 'a' ) )
           ECRIRE ( '_____Search in BST1_____' ) ;
           APPEL Rangequery ( R1 , Mot1 , Mot2 ) ;
          
       SINON
           SI ( ( CARACT ( Mot1 , 1 ) > 'Y' ) OU ( CARACT ( Mot1 , 1 ) > 'Z' ) OU ( CARACT ( Mot1 , 1 ) > 'a' ) )
               ECRIRE ( '_____Search in BST2_____' ) ;
               APPEL Rangequery ( R2 , Mot1 , Mot2 ) ;
              
           SINON
               ECRIRE ( '_____Search in BST3_____' ) ;
               APPEL Rangequery ( R3 , Mot1 , Mot2 ) ;
              
           FSI ;
          
       FSI ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Rangequery ( R , A , B )
  /*optimized*/
   SOIENT
       R , P DES ARB DE CHAINE ;
       A , B DES CHAINES ;
      
   DEBUT
       APPEL Searchsmallest ( R , A , P ) ;
       TQ ( P <> NIL )
           SI ( INFO ( P ) <= B )
               ECRIRE ( INFO ( P ) ) ;
               P := Next_inordre ( P ) ;
              
           FSI ;
          
       FTQ ;
      
   FIN
  /*-----------------------------------------------------------*/
   FONCTION Next_inordre ( P ) : ARB DE CHAINE
   SOIENT
       P UN ARB DE CHAINE ;
       Found UN BOOLEEN ;
      
   DEBUT
       SI FD ( P ) <> NIL
           P := FD ( P ) ;
           TQ ( FG ( P ) <> NIL )
               P := FG ( P ) ;
              
           FTQ ;
          
       SINON
           Found := FAUX ;
           TQ ( ( PERE ( P ) <> NIL ) ET ( NON Found ) )
               SI FG ( PERE ( P ) ) = P
                   Found := VRAI ;
                  
               SINON
                   P := PERE ( P ) ;
                  
               FSI ;
              
           FTQ ;
           P := PERE ( P ) ;
          
       FSI ;
       Next_inordre := P ;
      
   FIN
  /*------------------------------------------------------------*/
   ACTION Searchsmallest ( R , Word , P )
  /* search in R the smallest value greater than or equal to Word  */
   SOIENT
       R , P , Q DES ARB DE CHAINE ;
       Word UNE CHAINE ;
      
   DEBUT
       TQ R <> NIL
           SI ( INFO ( R ) >= Word )
               Q := R ;
               R := FG ( R ) ;
              
           SINON
               R := FD ( R ) ;
              
           FSI ;
          
       FTQ ;
       P := Q ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION Inorder_traversal ( R ) ;
   SOIENT
       R UN ARB DE CHAINE ;
      
   DEBUT
       SI R <> NIL
           APPEL Inorder_traversal ( FG ( R ) ) ;
           ECRIRE ( INFO ( R ) ) ;
           APPEL Inorder_traversal ( FD ( R ) ) ;
          
       FSI ;
      
   FIN
  /*-----------------------------------------------------------*/
   ACTION File_gen_word
   SOIENT
       F UN FICHIER DE CHAINE BUFFER S ;
       I , N DES ENTIERS ;
      
   DEBUT
       OUVRIR ( F , 'F2.z' , 'N' ) ;
       POUR I := 1 , 20
           N := ALEANOMBRE ( 10 ) ;
           SI ( N = 0 )
               S := 'Y' + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
              
           FSI ;
           SI ( N = 1 )
               S := 'Z' + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
              
           FSI ;
           SI ( N = 2 )
               S := 'a' + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
              
           FSI ;
           SI ( N > 2 )
               S := ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
              
           FSI ;
           ECRIRESEQ ( F , S ) ;
          
       FPOUR ;
       FERMER ( F ) ;
      
   FIN
  /*-------------------------------------------------------------*/
   ACTION Menu
   SOIENT
       Mainchoice , Choice1 , Choix , Choice2 UN ENTIER ;
       H UN ENTIER ;
       R , R1 , R2 , R3 , P DES ARB DE CHAINE ;
       Word , Mot1 , Mot2 DES CHAINES ;
      
   DEBUT
       Mainchoice := 0 ;
       Choice1 := 0 ;
       Choice2 := 0 ;
       Choix := 0 ;
       TQ Mainchoice <> 3
           ECRIRE ( '____________PRINCIPLE MENU____________' ) ;
           ECRIRE ( '1. Part I : Initial Tree Construction & Verification' ) ;
           ECRIRE ( '2. Part II : Word Search Operations' ) ;
           ECRIRE ( '3. Quitter' ) ;
           LIRE ( Mainchoice ) ;
           SI Mainchoice = 1
               TQ Choice1 <> 4
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( '______Initial Tree Construction & Verification______' ) ;
                   ECRIRE ( '1. Generate a file F containing N randomly generated words (N ≥ 100).' ) ;
                   ECRIRE ( '2. Construct BST1, BST2, and BST3 from F.' ) ;
                   ECRIRE ( '3. Perform operations on BST:' ) ;
                   ECRIRE ( '4. Back to main menu.' ) ;
                   ECRIRE ( ' ' ) ;
                   LIRE ( Choice1 ) ;
                   SI Choice1 = 1
                       APPEL File_gen_word ;
                       ECRIRE ( 'Done Succesfuly' ) ;
                      
                   FSI ;
                   SI Choice1 = 2
                       APPEL Createbst1 ( R1 ) ;
                       APPEL Createbst2 ( R2 ) ;
                       APPEL Createbst3 ( R3 ) ;
                       ECRIRE ( 'Done Succesfuly' ) ;
                      
                   FSI ;
                   SI Choice1 = 3
                       TQ Choix <> 5
                           ECRIRE ( ' ' ) ;
                           ECRIRE ( '______Opérations sur les arbres______' ) ;
                           ECRIRE ( '1. Count the number of words starting with X, Y, and Z.' ) ;
                           ECRIRE ( '2. Compute the depth of the tree. ' ) ;
                           ECRIRE ( '3. Perform an inorder traversal. ' ) ;
                           ECRIRE ( '4. Compute and display the number of nodes ' ) ;
                          /*,starting with X, Y, and Z for each level. */
                           ECRIRE ( '5. Back to previous menu.' ) ;
                           ECRIRE ( ' ' ) ;
                           LIRE ( Choix ) ;
                           SI Choix = 1
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST1:_____' ) ;
                               APPEL Count ( R1 ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST2:_____' ) ;
                               APPEL Count ( R2 ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST3:_____' ) ;
                               APPEL Count ( R3 ) ;
                               ECRIRE ( ' ' ) ;
                              
                           FSI ;
                           SI Choix = 2
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( 'Depth of BST1: ' , Depth ( R1 ) ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( 'Depth of BST2: ' , Depth ( R2 ) ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( 'Depth of BST3: ' , Depth ( R3 ) ) ;
                               ECRIRE ( ' ' ) ;
                              
                           FSI ;
                           SI Choix = 3
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST1:_____' ) ;
                               APPEL Inorder_traversal ( R1 ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST2:_____' ) ;
                               APPEL Inorder_traversal ( R2 ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST3:_____' ) ;
                               APPEL Inorder_traversal ( R3 ) ;
                               ECRIRE ( ' ' ) ;
                              
                           FSI ;
                           SI Choix = 4
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST1:_____' ) ;
                               APPEL Levelcount ( R1 ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST2:_____' ) ;
                               APPEL Levelcount ( R2 ) ;
                               ECRIRE ( ' ' ) ;
                               ECRIRE ( '_____BST3:_____' ) ;
                               APPEL Levelcount ( R3 ) ;
                               ECRIRE ( ' ' ) ;
                              
                           FSI ;
                          
                       FTQ ;
                      
                   FSI ;
                  
               FTQ ;
              
           FSI ;
           SI Mainchoice = 2
               TQ Choice2 <> 3
                   ECRIRE ( ' ' ) ;
                   ECRIRE ( '______Word Search Operations______' ) ;
                   ECRIRE ( '1. Single Word Search. ' ) ;
                   ECRIRE ( '2. Range Search: [Word1, Word2]. ' ) ;
                   ECRIRE ( '3. Back to main menu.' ) ;
                   ECRIRE ( ' ' ) ;
                   LIRE ( Choice2 ) ;
                   SI Choice2 = 1
                       ECRIRE ( ' ' ) ;
                       ECRIRE ( 'ENTER Word to search: ' ) ;
                       LIRE ( Word ) ;
                       APPEL Searchbst ( R1 , R2 , R3 , Word , P ) ;
                       ECRIRE ( ' ' ) ;
                      
                   FSI ;
                   SI Choice2 = 2
                       ECRIRE ( ' ' ) ;
                       ECRIRE ( 'ENTER Word1 :' ) ;
                       LIRE ( Mot1 ) ;
                       ECRIRE ( 'ENTER Word2 :' ) ;
                       LIRE ( Mot2 ) ;
                       APPEL Rangebst ( R1 , R2 , R3 , Mot1 , Mot2 ) ;
                       ECRIRE ( ' ' ) ;
                      
                   FSI ;
                  
               FTQ ;
              
           FSI ;
          
       FTQ ;
      
   FIN
