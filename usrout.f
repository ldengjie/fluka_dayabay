*$ CREATE USROUT.FOR
*COPY USROUT
*
*=== usrout ===========================================================*
*
      SUBROUTINE USROUT ( WHAT, SDUM )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
      INCLUDE '(IMGDRAW)'
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1991-2005      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     USeR OUTput: this routine is called every time the USROCALL card *
*                  is found in the input stream                        *
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

      CALL FILECLOSE
        OPEN(UNIT=90,FILE="../NextSeedNum",STATUS="REPLACE")
           WRITE(90,*) NextSeedNum
        CLOSE(90)
*
      RETURN
*=== End of subroutine Usrout =========================================*
      END

