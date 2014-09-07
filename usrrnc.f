*$ CREATE USRRNC.FOR
*COPY USRRNC
*
*=== Usrrnc ===========================================================*
*
      SUBROUTINE USRRNC ( IZ, IA, IS, X, Y, Z, MREG, WEE, ICALL )
      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
      INCLUDE '(IMGDRAW)'

*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 2005-2005      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     USeR Residual NuClei:                                            *
*                                                                      *
*     Created on   06 april 2005   by    Alfredo Ferrari & Paola Sala  *
*                                                   Infn - Milan       *
*                                                                      *
*     Last change on 06-apr-05     by    Alfredo Ferrari               *
*                                                                      *
*                                                                      *
*----------------------------------------------------------------------*
*
      CHARACTER*8 RGNAM
      DIMENSION KA (4), KZ (4), BRDAUG (4), T12DAU (4)
      DOUBLE PRECISION HafTime
      EXTERNAL TIM1O2, BDNOPT
      CALL GEOR2N ( MREG,RGNAM,IERR1)
C      if(MREG.gt.4) WRITE(*,*) 'RGNAM',RGNAM
C      if(RGNAM.eq.'SST'.or.RGNAM.eq.'MO'.or.RGNAM.eq.'OAT'.or.
C     &RGNAM.eq.'LS'.or.RGNAM.eq.'IAT'.or.RGNAM.eq.'GDLS') then
*isotope
        ISOMER = 0
        HafTime = TIM1O2 ( IA, IZ, KA, KZ, T12DAU, BRDAUG, ISOMER )
        if(HafTime>1E38) then
C            WRITE(*,*) 'USRRNC():stable'
        else
C            WRITE(*,*) 'USRRNC():',IZ,IA,X, Y, Z
            call filliso(EvtID,IZ,IA,X, Y, Z,MREG)
C            WRITE(*,*) 'FillIso : ',EvtID,IZ,IA,X, Y, Z
            IsoNum=IsoNum+1
        endif
C      endif
      RETURN
*=== End of subroutine Usrrnc =========================================*
      END
