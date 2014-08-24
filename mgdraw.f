*----------------------------------------------------------------------*
*                                                                      *
*     MaGnetic field trajectory DRAWing: actually this entry manages   *
*                                        all trajectory dumping for    *
*                                        drawing                       *
*                                                                      *
*     Created on   21 Aug 2014     by   Li Dengjie                     *
*     Last change   *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
      SUBROUTINE MGDRAW ( ICODE, MREG )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
      INCLUDE '(CASLIM)'
      INCLUDE '(COMPUT)'
      INCLUDE '(SOURCM)'
      INCLUDE '(FHEAVY)'
      INCLUDE '(FLKSTK)'
      INCLUDE '(GENSTK)'
      INCLUDE '(MGDDCM)'
      INCLUDE '(PAPROP)'
      INCLUDE '(QUEMGD)'
      INCLUDE '(SUMCOU)'
      INCLUDE '(TRACKR)'
      INCLUDE '(IMGDRAW)'
*
      DIMENSION DTQUEN ( MXTRCK, MAXQMG )
*
      LOGICAL LFCOPE
      SAVE LFCOPE
      DATA LFCOPE / .FALSE. /
*----------------------------------------------------------------------*
*                                                                      *
*     Icode = 1: call from Kaskad                                      *
*     Icode = 2: call from Emfsco                                      *
*     Icode = 3: call from Kasneu                                      *
*     Icode = 4: call from Kashea                                      *
*     Icode = 5: call from Kasoph                                      *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
      IF ( .NOT. LFCOPE ) THEN
         LFCOPE = .TRUE.
         IF ( KOMPUT .EQ. 2 ) THEN
            FILNAM = '/'//CFDRAW(1:8)//' DUMP A'
         ELSE
            FILNAM = CFDRAW
         END IF
C         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
C     &          'FORMATTED' )
      END IF
C      DKineE=0
C      if(JTRACK.eq.308) then
C          DKineE=ETRACK-AM(8)
C      else if(JTRACK.lt.200 .and. JTRACK.gt.0) then
C          DKineE=ETRACK-AM(JTRACK)
C      else
C          DKineE=ETRACK
C      endif
C      WRITE (*,*) 'MGDRAW(',NRGNAM,')'
C      WRITE (*,*) NTRACK, MTRACK, 'Particle:', JTRACK,
C     &               'generation:',LTRACK,
C     &               'KineEng:',DKineE,
C     &               'age:',ATRACK,NCASE,NCASES
C      WRITE (*,*) 'xyz : ',( SNGL (XTRACK (I)), SNGL (YTRACK (I)),
C     &                 SNGL (ZTRACK (I)),'||', I = 0, NTRACK )
C
C      WRITE (*,*) 'eng : ',( SNGL (DTRACK (I)),'||', I = 1, MTRACK )
C      WRITE (*,*) 'length',SNGL (CTRACK)

C      WRITE(*,*) 'NRGNAM',NRGNAM
C      if(NRGNAM.eq.'STONE') then
C          WRITE(*,*) 'NRGNAM:STONE'
C      else
C          WRITE(*,*) 'NRGNAM:',NRGNAM
C      endif
      if(NRGNAM.eq.'LS'.or.NRGNAM.eq.'GDLS') then
         DO I=1,MTRACK
C            WRITE(*,*) 'DTRACK (I):',DTRACK (I)
            if(DTRACK (I).gt.0) then
                IICode=0
                if(LTRACK.gt.1) then
                    ISpaMaId=ISPUSR(2)
                    ISpaMaTy=ISPUSR(1)
                else
                    ISpaMaId=0
                    ISpaMaTy=0
                endif
               call fillspa(NCASE,XTRACK (I),YTRACK (I),ZTRACK (I),
     &DTRACK (I),ATRACK,JTRACK,IICode,ISpaMaId,ISpaMaTy)
           write(*,*) 'fillspa',NCASE,XTRACK (I),YTRACK (I),ZTRACK (I),
     &DTRACK (I),ATRACK,JTRACK,IICode,ISpaMaId,ISpaMaTy
            endif
         ENDDO
      endif

*  +-------------------------------------------------------------------*
*  |  Quenching is activated
      IF ( LQEMGD ) THEN
         IF ( MTRACK .GT. 0 ) THEN
            RULLL  = ZERZER
            CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
C            WRITE (*,*) 'que : ',((SNGL(DTQUEN(I,JBK)),'||',I=1,MTRACK),
C     &                         JBK = 1, NQEMGD )
         END IF
      END IF
C      WRITE (*,*) ''


*  |  End of quenching
*  +-------------------------------------------------------------------*
      RETURN
*
*======================================================================*
*                                                                      *
*     Boundary-(X)crossing DRAWing:                                    *
*                                                                      *
*     Icode = 1x: call from Kaskad                                     *
*             19: boundary crossing                                    *
*     Icode = 2x: call from Emfsco                                     *
*             29: boundary crossing                                    *
*     Icode = 3x: call from Kasneu                                     *
*             39: boundary crossing                                    *
*     Icode = 4x: call from Kashea                                     *
*             49: boundary crossing                                    *
*     Icode = 5x: call from Kasoph                                     *
*             59: boundary crossing                                    *
*                                                                      *
*======================================================================*
*                                                                      *
      ENTRY BXDRAW ( ICODE, MREG, NEWREG, XSCO, YSCO, ZSCO )
      CALL GEOR2N ( MREG,MRGNAM,IERR1)
      CALL GEOR2N ( NEWREG,NRGNAM,IERR2)
C      WRITE (*,*) 'lidj BXDRAW (',MRGNAM,'->',NRGNAM,')'
C      WRITE (*,*) ''
      IF (NRGNAM.EQ.'OWS') THEN
C          IF(any(OwsInitP(1,1:3)).EQ.0) then
          IF(DOT_PRODUCT(OwsInitP(1,1:3),OwsInitP(1,1:3)).eq.0) then
              OwsInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              OwsInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'IWS') THEN
          IF(DOT_PRODUCT(IwsInitP(1,1:3),IwsInitP(1,1:3)).EQ.0) then
              IwsInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              IwsInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'MO') THEN
          IF(DOT_PRODUCT(MoInitP(1,1:3),MoInitP(1,1:3)).EQ.0) then
              MoInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              MoInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'LS') THEN
          IF(DOT_PRODUCT(LsInitP(1,1:3),LsInitP(1,1:3)).EQ.0) then
              LsInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              LsInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'GDLS') THEN
          IF(DOT_PRODUCT(GdInitP(1,1:3),GdInitP(1,1:3)).EQ.0) then
              GdInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              GdInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE

      END IF

      IF (MRGNAM.EQ.'OWS') THEN
          IF(DOT_PRODUCT(OwsFinaP(1,1:3),OwsFinaP(1,1:3)).EQ.0) then
              OwsFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              OwsFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'IWS') THEN
          IF(DOT_PRODUCT(IwsFinaP(1,1:3),IwsFinaP(1,1:3)).EQ.0) then
              IwsFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              IwsFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'MO') THEN
          IF(DOT_PRODUCT(MoFinaP(1,1:3),MoFinaP(1,1:3)).EQ.0) then
              MoFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              MoFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'LS') THEN
          IF(DOT_PRODUCT(LsFinaP(1,1:3),LsFinaP(1,1:3)).EQ.0) then
              LsFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              LsFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'GDLS') THEN
          IF(DOT_PRODUCT(GdFinaP(1,1:3),GdFinaP(1,1:3)).EQ.0) then
              GdFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              GdFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE
      END IF

      RETURN
*
*======================================================================*
*                                                                      *
*     Event End DRAWing:                                               *
*                                                                      *
*======================================================================*
*                                                                      *
      ENTRY EEDRAW ( ICODE )
C      WRITE (*,*) 'lidj EEDRAW()'
C      WRITE (*,*) ''
*muon
      OwsLen=sqrt(DOT_PRODUCT(OwsFinaP(1,1:3)-OwsInitP(1,1:3),
     &OwsFinaP(1,1:3)-OwsInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &OwsFinaP(2,1:3)-OwsInitP(2,1:3),OwsFinaP(2,1:3)-OwsInitP(2,1:3)))
      IwsLen=sqrt(DOT_PRODUCT(IwsFinaP(1,1:3)-IwsInitP(1,1:3),
     &IwsFinaP(1,1:3)-IwsInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &IwsFinaP(2,1:3)-IwsInitP(2,1:3),IwsFinaP(2,1:3)-IwsInitP(2,1:3)))
      MoLen=sqrt(DOT_PRODUCT(MoFinaP(1,1:3)-MoInitP(1,1:3),
     &MoFinaP(1,1:3)-MoInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &MoFinaP(2,1:3)-MoInitP(2,1:3),MoFinaP(2,1:3)-MoInitP(2,1:3)))
      LsLen=sqrt(DOT_PRODUCT(LsFinaP(1,1:3)-LsInitP(1,1:3),
     &LsFinaP(1,1:3)-LsInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &LsFinaP(2,1:3)-LsInitP(2,1:3),LsFinaP(2,1:3)-LsInitP(2,1:3)))
      GdLen=sqrt(DOT_PRODUCT(GdFinaP(1,1:3)-GdInitP(1,1:3),
     &GdFinaP(1,1:3)-GdInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &GdFinaP(2,1:3)-GdInitP(2,1:3),GdFinaP(2,1:3)-GdInitP(2,1:3)))

      call fillmuon(NCASE,MuCharge,MuInitE,MuInitT,MuInitP(1),
     &MuInitP(2),MuInitP(3),
     &MuInitTP(1),MuInitTP(2),MuInitTP(3),OwsLen,IwsLen,MoLen,
     &LsLen,GdLen,
     &NeuNum,IsoNum)
      WRITE(*,*) 'fillmuon',NCASE,MuCharge,MuInitE,MuInitT,MuInitP(1),
     &MuInitP(2),MuInitP(3),
     &MuInitTP(1),MuInitTP(2),MuInitTP(3),OwsLen,IwsLen,MoLen,
     &LsLen,GdLen,
     &NeuNum,IsoNum
*neutron
      if(NeuNum.gt.0) then
          DO I=1,NeuNum
        call fillneu(NCASE,NeuInitE(I),NeuInitT(I),
     &NeuInitP(I,1),NeuInitP(I,2),NeuInitP(I,3),
     &NeuCapP(I,1),NeuCapP(I,2),NeuCapP(I,3),
     &NeuCapT(I),NeuGamaE(I),NeuGamaN(I),
     &NeuMaID(I),NeuType(I))
        WRITE(*,*) 'fillneu',NCASE,NeuInitE(I),NeuInitT(I),
     &NeuInitP(I,1),NeuInitP(I,2),NeuInitP(I,3),
     &NeuCapP(I,1),NeuCapP(I,2),NeuCapP(I,3),
     &NeuCapT(I),NeuGamaE(I),NeuGamaN(I),
     &NeuMaID(I),NeuType(I)
          enddo
      endif
*
      RETURN
*
*======================================================================*
*                                                                      *
*     ENergy deposition DRAWing:                                       *
*                                                                      *
*     Icode = 1x: call from Kaskad                                     *
*             10: elastic interaction recoil                           *
*             11: inelastic interaction recoil                         *
*             12: stopping particle                                    *
*             13: pseudo-neutron deposition                            *
*             14: escape                                               *
*             15: time kill                                            *
*     Icode = 2x: call from Emfsco                                     *
*             20: local energy deposition (i.e. photoelectric)         *
*             21: below threshold, iarg=1                              *
*             22: below threshold, iarg=2                              *
*             23: escape                                               *
*             24: time kill                                            *
*     Icode = 3x: call from Kasneu                                     *
*             30: target recoil                                        *
*             31: below threshold                                      *
*             32: escape                                               *
*             33: time kill                                            *
*     Icode = 4x: call from Kashea                                     *
*             40: escape                                               *
*             41: time kill                                            *
*             42: delta ray stack overflow                             *
*     Icode = 5x: call from Kasoph                                     *
*             50: optical photon absorption                            *
*             51: escape                                               *
*             52: time kill                                            *
*                                                                      *
*======================================================================*
*                                                                      *
      ENTRY ENDRAW ( ICODE, MREG, RULL, XSCO, YSCO, ZSCO )
      IF ( .NOT. LFCOPE ) THEN
         LFCOPE = .TRUE.
         IF ( KOMPUT .EQ. 2 ) THEN
            FILNAM = '/'//CFDRAW(1:8)//' DUMP A'
         ELSE
            FILNAM = CFDRAW
         END IF
C         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
C     &          'FORMATTED' )
      END IF
C      DKineE=0
C      if(JTRACK.eq.308) then
C          DKineE=ETRACK-AM(8)
C      else if(JTRACK.lt.200 .and. JTRACK.gt.0) then
C          DKineE=ETRACK-AM(JTRACK)
C      else
C          DKineE=ETRACK
C      endif
C      WRITE (*,*) 'lidj ENDRAW()','ICODE:',ICODE
C      WRITE (*,*)  NTRACK, MTRACK, 'Particle:',JTRACK,
C     &               'generation:',LTRACK,
C     &               'KineEng:', DKineE,
C     &               'age:',ATRACK,NCASE,NCASES
C      WRITE (*,*)  'xyz : ',SNGL (XSCO), SNGL (YSCO), SNGL (ZSCO)
C      WRITE (*,*)  'eng : ',SNGL (RULL)
      if(NRGNAM.eq.'LS'.or.NRGNAM.eq.'GDLS') then
                IICode=ICODE
                if(LTRACK.gt.1) then
                    ISpaMaId=ISPUSR(2)
                    ISpaMaTy=ISPUSR(1)
                else
                    ISpaMaId=0
                    ISpaMaTy=0
                endif
               call fillspa(NCASE,XSCO,YSCO,ZSCO,
     &RULL,ATRACK,QenE,JTRACK,IICode,ISpaMaId,ISpaMaTy)
               write(*,*) 'fillspa',NCASE,XSCO,YSCO,ZSCO,
     &RULL,ATRACK,QenE,JTRACK,IICode,ISpaMaId,ISpaMaTy
      endif

*  +-------------------------------------------------------------------*
*  |  Quenching is activated : calculate quenching factor
*  |  and store quenched energy in DTQUEN(1, jbk)
      IF ( LQEMGD ) THEN
         RULLL = RULL
         CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
C         WRITE (*,*) 'que : ',(SNGL (DTQUEN(1, JBK)),'||',JBK=1,NQEMGD)
      END IF
C      WRITE (*,*) ''
*  |  end quenching
*  +-------------------------------------------------------------------*
      RETURN
*
*======================================================================*
*                                                                      *
*     SOurce particle DRAWing:                                         *
*                                                                      *
*======================================================================*
*
      ENTRY SODRAW
      IF ( .NOT. LFCOPE ) THEN
         LFCOPE = .TRUE.
         IF ( KOMPUT .EQ. 2 ) THEN
            FILNAM = '/'//CFDRAW(1:8)//' DUMP A'
         ELSE
            FILNAM = CFDRAW
         END IF
      END IF
C      WRITE (*,*) 'lidj SODRAW()'
C      WRITE (*,*)   'Particle:',ILOFLK(1),
C     &               'generation:',LOFLK(1),
C     &               'KineEng:', SNGL (TKEFLK(1)),
C     &               'age:',AGESTK(1)
C      WRITE (*,*)  'xyz : ',SNGL(XFLK(1)),SNGL(YFLK(1)), SNGL (ZFLK(1))
C      WRITE (*,*) ''
*
      MuInitT=AGESTK(1)
      MuInitE=TKEFLK(1)
      MuInitP=[XFLK(1),YFLK(1),ZFLK(1)]
      MuInitTP=[TXFLK(1),TYFLK(1),TZFLK(1)]
      if(ILOFLK(1).eq.10) then
         MuCharge=1
      else
         MuCharge=-1
      endif

*
*  |
*  +-------------------------------------------------------------------*
      RETURN
*
*======================================================================*
*                                                                      *
*     USer dependent DRAWing:                                          *
*                                                                      *
*     Icode = 10x: call from Kaskad                                    *
*             100: elastic   interaction secondaries                   *
*             101: inelastic interaction secondaries                   *
*             102: particle decay  secondaries                         *
*             103: delta ray  generation secondaries                   *
*             104: pair production secondaries                         *
*             105: bremsstrahlung  secondaries                         *
*             110: decay products                                      *
*     Icode = 20x: call from Emfsco                                    *
*             208: bremsstrahlung secondaries                          *
*             210: Moller secondaries                                  *
*             212: Bhabha secondaries                                  *
*             214: in-flight annihilation secondaries                  *
*             215: annihilation at rest   secondaries                  *
*             217: pair production        secondaries                  *
*             219: Compton scattering     secondaries                  *
*             221: photoelectric          secondaries                  *
*             225: Rayleigh scattering    secondaries                  *
*             237: mu pair     production secondaries                  *
*     Icode = 30x: call from Kasneu                                    *
*             300: interaction secondaries                             *
*     Icode = 40x: call from Kashea                                    *
*             400: delta ray  generation secondaries                   *
*  For all interactions secondaries are put on GENSTK common (kp=1,np) *
*  but for KASHEA delta ray generation where only the secondary elec-  *
*  tron is present and stacked on FLKSTK common for kp=npflka          *
*                                                                      *
*======================================================================*
*
      ENTRY USDRAW ( ICODE, MREG, XSCO, YSCO, ZSCO )
      IF ( .NOT. LFCOPE ) THEN
         LFCOPE = .TRUE.
         IF ( KOMPUT .EQ. 2 ) THEN
            FILNAM = '/'//CFDRAW(1:8)//' DUMP A'
         ELSE
            FILNAM = CFDRAW
         END IF
C         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
C     &          'FORMATTED' )
      END IF
* No output by default:
C      WRITE (*,*) 'lidj USDRAW(',ICODE,')'
C      DKineE=0
C      if(JTRACK.eq.308) then
C          DKineE=ETRACK-AM(8)
C      else if(JTRACK.lt.200 .and. JTRACK.gt.0) then
C          DKineE=ETRACK-AM(JTRACK)
C      else
C          DKineE=ETRACK
C      endif
C      WRITE (*,*)  NTRACK, MTRACK, 'Particle:',JTRACK,
C     &               'generation:',LTRACK,
C     &               'KineEng:', DKineE,
C     &               'age:',ATRACK,NCASE,NCASES
C      WRITE (*,*)  'xyz : ',SNGL (XSCO), SNGL (YSCO), SNGL (ZSCO)
C      WRITE (*,*) ''
C      IF( JTRACK.EQ.1) THEN
C          IF(ETRACK.GT.AM(JTRACK)) THEN
C              PRINT *,"-------> Filling histo"
C              CALL treefill(JTRACK,
C     +                       (ETRACK-AM(JTRACK)),XSCO,YSCO,ZSCO,
C     +                       CXTRCK,CYTRCK,CZTRCK)
C          ENDIF
C      ENDIF
C      WRITE(*,*) '*GENSTK'
C      DO IP = 1, NP 
C          WRITE(*,*) '+>',KPART(IP),TKI (IP),AGESEC(IP)
C      END DO 
C      WRITE(*,*) '*FHEAVY'
C      DO IP = 1,NPHEAV 
C          WRITE(*,*) '=>',KHEAVY(IP),TKHEAV(IP),AGHEAV(IP),
C     &               ICHEAV(KHEAVY(IP)),IBHEAV(KHEAVY(IP)),
C     &               ANHEAV(KHEAVY(IP))
C      END DO 
C      WRITE(*,*) '*RESNUC'
C      WRITE(*,*) ICESTR,IBESTR,'->',ICRES,IBRES,AMNRES,AMMRES

*neutr
* ISPUSR 1.reaction type 2.parent'd id 3.neutron num 4.isotopes num ?.gamma num 
      ISPUSR(1)=ICODE
      ISPUSR(2)=JTRACK
* SPAUSR 1.parent's age
      SPAUSR(1)=ATRACK

      if(JTRACK.eq.8)then
          IsCap=1
          DO IP = 1, NP 
             if(KPART(IP).ne.7) then
                IsCap=0
             endif
          END DO 
          if(IsCap.eq.1) then
             DO IP = 1, NP 
                 if(KPART(IP).eq.7) then
                     NeuGamaN(ISPUSR(3))=NeuGamaN(ISPUSR(3))+1
                     NeuGamaE(ISPUSR(3))=NeuGamaE(ISPUSR(3))+TKI (IP)
                     NeuCapT(ISPUSR(3))=AGESEC(IP)+ATRACK
                     NeuCapP(ISPUSR(3),1:3)=[XSCO,YSCO,ZSCO]
                 endif
             END DO 
          endif
      endif
*Michel electron
      if(LTRACK.eq.1 .and. ICODE.eq.102) then
          DO IP = 1, NP 
             if(KPART(IP).eq.3) then
           call fillmi(NCASE,TKI(IP),AGESEC(IP)+ATRACK,XSCO,YSCO,ZSCO)
      write(*,*) 'fillmi',NCASE,TKI(IP),AGESEC(IP)+ATRACK,XSCO,YSCO,ZSCO
             endif
          END DO 
          
      endif

      RETURN
*=== End of subrutine Mgdraw ==========================================*
      END

