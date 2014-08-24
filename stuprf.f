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
*neutron
      if(KPART(NPSECN).eq.8 .and. NP.ne.1) then
         if(ISPUSR(3).eq.0) then
             NeuNum=NeuNum+1
C             WRITE(*,*) 'stuprf:NeuNum ',NeuNum
*ISPUSR 1.reaction type 3 neutron num 4.isotopes num ?.gamma num 
*SPAUSR 1.parent's age
             ISPARK(3,NPFLKA)=NeuNum !then ISPARK->ISPUSR
             NeuMaID(NeuNum)=IJ
             NeuType(NeuNum)=ISPUSR(1)
             NeuInitT(NeuNum)=AGESEC(NPSECN)+SPAUSR(1)
             NeuInitE(NeuNum)=TKI (NPSECN)
             NeuInitP(NeuNum,1:3)=[XX, YY, ZZ]
         end if

      end if
*  Increment the track number and put it into the last flag:
      IF ( NPSECN .GT. NPPRMR ) THEN
         IF ( NTRCKS .EQ. 2000000000 ) NTRCKS = -2000000000
         NTRCKS = NTRCKS + 1
         ISPARK (MKBMX2,NPFLKA) = NTRCKS
      END IF
      RETURN
*=== End of subroutine Stuprf =========================================*
      END

