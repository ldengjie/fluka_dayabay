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
       if(ISPUSR(2).eq.8) then
          if(ISPUSR(1).eq.101) then
             if(TKI (NPSECN).ne.MaxNeuE) then
C                 WRITE(*,*) 'TKI (NPSECN):MaxNeuE',TKI(NPSECN),MaxNeuE
                NeuNum=NeuNum+1
*ISPUSR 1.reaction type 2.parent'd id 3.neutron num 4.isotopes num ?.gamma num 
*SPAUSR 1.parent's age
                ISPARK(3,NPFLKA)=NeuNum !then ISPARK->ISPUSR
                NeuMaID(NeuNum)=IJ
                NeuType(NeuNum)=ISPUSR(1)
                NeuInitT(NeuNum)=AGESEC(NPSECN)+SPAUSR(1)
                NeuInitE(NeuNum)=0
                NeuInitP(NeuNum,1:3)=[XX, YY, ZZ]
                NeuInitVm=MREG
C                WRITE(*,*) 'Find a secondary neutron'
             endif
          endif
       else
         NeuNum=NeuNum+1
         ISPARK(3,NPFLKA)=NeuNum !then ISPARK->ISPUSR
         NeuMaID(NeuNum)=IJ
         NeuType(NeuNum)=ISPUSR(1)
         NeuInitT(NeuNum)=AGESEC(NPSECN)+SPAUSR(1)
C         NeuInitE(NeuNum)=TKI (NPSECN)
         NeuInitE(NeuNum)=0
         NeuInitP(NeuNum,1:3)=[XX, YY, ZZ]
C                WRITE(*,*) 'Find a primary neutron'
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

