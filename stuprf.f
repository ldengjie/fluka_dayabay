*
      SUBROUTINE STUPRF ( IJ, MREG, XX, YY, ZZ, NPSECN, NPPRMR )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
      INCLUDE '(EVTFLG)'
      INCLUDE '(FLKSTK)'
      INCLUDE '(TRACKR)'
      INCLUDE '(GENSTK)'
      INCLUDE '(IMGDRAW)'
      INCLUDE '(EMFSTK)'
*
      LOUSE   (NPFLKA)  = LLOUSE
      DO 100 ISPR = 1, MKBMX1
         SPAREK (ISPR,NPFLKA) = SPAUSR (ISPR)
  100 CONTINUE
      DO 200 ISPR = 1, MKBMX2
         ISPARK (ISPR,NPFLKA) = ISPUSR (ISPR)
  200 CONTINUE
C      WRITE(*,*) "Save into stack : ",KPART(NPSECN),'NP : ',NP
*save initial volume
         ISPARK (5,NPFLKA) = MREG
*neutron
      if(KPART(NPSECN).EQ.8) then
C        IF (NeuCount .GE. 1) THEN
C            WRITE(*,*) 'STU101300NoSubOne'
C            if(ISPUSR(2).eq.8 .and. TKI (NPSECN).ne.MaxNeuE) then
C                WRITE(*,*) 'STU101300SubOne'
C            elseif(ISPUSR(2).ne.8) then
C                WRITE(*,*) 'STU101300SubOne'
C            endif
C        ENDIF
       if(ISPUSR(2).eq.8) then
          if(TKI (NPSECN).ne.MaxNeuE) then
C              WRITE(*,*) 'SubOneSTU101300',IJ,"ReactionType",ISPUSR(1)
             if(ISPUSR(1).eq.101) then
                NeuNum=NeuNum+1
* ISPUSR 1.reaction type 2.parent'd id 3.neutron num 4.isotopes num 5.initial volume 6.initial volume of muon's daughter ?.gamma num 
*SPAUSR 1.parent's age 2.parent's energy
                ISPARK(3,NPFLKA)=NeuNum !then ISPARK->ISPUSR
                NeuMaID(NeuNum)=IJ
                NeuMaE(NeuNum)=SPAUSR(2)
                NeuType(NeuNum)=ISPUSR(1)
                NeuInitT(NeuNum)=AGESEC(NPSECN)+SPAUSR(1)
                NeuInitE(NeuNum)=0
                NeuInitP(NeuNum,1:3)=[XX, YY, ZZ]
                NeuInitVm(NeuNum)=MREG
                NeuDauVm(NeuNum)=ISPUSR(6)
C                WRITE(*,*) 'MotherNumber',IJ,"ReactionType",ISPUSR(1)
             endif
          endif
       else
C                 WRITE(*,*) 'SubOneSTU101300'
         NeuNum=NeuNum+1
         ISPARK(3,NPFLKA)=NeuNum !then ISPARK->ISPUSR
         NeuMaID(NeuNum)=IJ
         NeuMaE(NeuNum)=SPAUSR(2)
C         if(IJ.eq.7) then
C            WRITE(*,*) 'neutron from gamma'
C         endif
         NeuType(NeuNum)=ISPUSR(1)
         NeuInitT(NeuNum)=AGESEC(NPSECN)+SPAUSR(1)
         NeuInitE(NeuNum)=0
         NeuInitP(NeuNum,1:3)=[XX, YY, ZZ]
         NeuInitVm(NeuNum)=MREG
         NeuDauVm(NeuNum)=ISPUSR(6)
C                WRITE(*,*) 'MotherNumber',IJ,"ReactionType",ISPUSR(1)
       endif
      endif
*  Increment the track number and put it into the last flag:
      IF ( NPSECN .GT. NPPRMR ) THEN
         IF ( NTRCKS .EQ. 2000000000 ) NTRCKS = -2000000000
         NTRCKS = NTRCKS + 1
         ISPARK (MKBMX2,NPFLKA) = NTRCKS
      END IF
      RETURN
*=== End of subroutine Stuprf =========================================*
      END

