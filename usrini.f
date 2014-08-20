*$ CREATE USRINI.FOR
*COPY USRINI
*
*=== usrini ===========================================================*
*
      SUBROUTINE USRINI ( WHAT, SDUM )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1991-2005      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     USeR INItialization: this routine is called every time the       *
*                          USRICALL card is found in the input stream  *
*                                                                      *
*                                                                      *
*     Created on 01 january 1991   by    Alfredo Ferrari & Paola Sala  *
*                                                   Infn - Milan       *
*                                                                      *
*     Last change on 20-mar-05     by    Alfredo Ferrari               *
*                                                                      *
*                                                                      *
*----------------------------------------------------------------------*
*
      DIMENSION WHAT (6)
      CHARACTER SDUM*8
*
      REAL *8 PIPPO
*
*  Don't change the following line:
      LUSRIN = .TRUE.
* *** Write from here on *** *
      PIPPO = 2.5D0
      CALL myusrini(PIPPO);
      RETURN
*=== End of subroutine Usrini =========================================*
      END

