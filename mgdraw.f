*$ CREATE MGDRAW.FOR
*COPY MGDRAW
*                                                                      *
*=== mgdraw ===========================================================*
*                                                                      *
      SUBROUTINE MGDRAW ( ICODE, MREG )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1990-2013      by        Alfredo Ferrari           *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     MaGnetic field trajectory DRAWing: actually this entry manages   *
*                                        all trajectory dumping for    *
*                                        drawing                       *
*                                                                      *
*     Created on   01 March 1990   by        Alfredo Ferrari           *
*                                              INFN - Milan            *
*     Last change   12-Nov-13      by        Alfredo Ferrari           *
*                                              INFN - Milan            *
*                                                                      *
*----------------------------------------------------------------------*
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
*
      DIMENSION DTQUEN ( MXTRCK, MAXQMG )
*
      CHARACTER*20 FILNAM
      CHARACTER*8 MRGNAM
      CHARACTER*8 NRGNAM
      LOGICAL LFCOPE
      SAVE LFCOPE
      DATA LFCOPE / .FALSE. /
*
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
         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
     &          'FORMATTED' )
      END IF
      WRITE (*,*) 'MGDRAW()'
      WRITE (*,*) NTRACK, MTRACK, 'Particle:', JTRACK,
     &               'generation:',LTRACK,
     &               'totalEng:', SNGL (ETRACK),
     &               'age:',ATRACK,NCASE,NCASES
      WRITE (*,*) 'xyz : ',( SNGL (XTRACK (I)), SNGL (YTRACK (I)),
     &                 SNGL (ZTRACK (I)),'||', I = 0, NTRACK )

      WRITE (*,*) 'eng : ',( SNGL (DTRACK (I)),'||', I = 1, MTRACK )
      WRITE (*,*) 'length',SNGL (CTRACK)
*  +-------------------------------------------------------------------*
*  |  Quenching is activated
      IF ( LQEMGD ) THEN
         IF ( MTRACK .GT. 0 ) THEN
            RULLL  = ZERZER
            CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
            WRITE (*,*) 'que : ',((SNGL(DTQUEN(I,JBK)),'||',I=1,MTRACK),
     &                         JBK = 1, NQEMGD )
         END IF
      END IF
      WRITE (*,*) ''
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
      WRITE (*,*) 'lidj BXDRAW (',MRGNAM,'->',NRGNAM,')'
      WRITE (*,*) ''

         IF( JTRACK.EQ.1) THEN
            IF(ETRACK.GT.AM(JTRACK)) THEN
               PRINT *,"-------> Filling histo"
               CALL treefill(JTRACK,
     +                       (ETRACK-AM(JTRACK)),XSCO,YSCO,ZSCO,
     +                       CXTRCK,CYTRCK,CZTRCK)
            ENDIF
         ENDIF

      RETURN
*
*======================================================================*
*                                                                      *
*     Event End DRAWing:                                               *
*                                                                      *
*======================================================================*
*                                                                      *
      ENTRY EEDRAW ( ICODE )
      WRITE (*,*) 'lidj EEDRAW()'
      WRITE (*,*) ''
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
         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
     &          'FORMATTED' )
      END IF
      WRITE (*,*) 'lidj ENDRAW()','ICODE:',ICODE
      WRITE (*,*)  NTRACK, MTRACK, 'Particle:',JTRACK,
     &               'generation:',LTRACK,
     &               'totalEng:', SNGL (ETRACK),
     &               'age:',ATRACK,NCASE,NCASES
      WRITE (*,*)  'xyz : ',SNGL (XSCO), SNGL (YSCO), SNGL (ZSCO)
      WRITE (*,*)  'eng : ',SNGL (RULL)
*  +-------------------------------------------------------------------*
*  |  Quenching is activated : calculate quenching factor
*  |  and store quenched energy in DTQUEN(1, jbk)
      IF ( LQEMGD ) THEN
         RULLL = RULL
         CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
         WRITE (*,*) 'que : ',(SNGL (DTQUEN(1, JBK)),'||',JBK=1,NQEMGD)
      END IF
      WRITE (*,*) ''
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
C         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
C     &          'UNFORMATTED' )
      END IF
      WRITE (*,*) 'lidj SODRAW()'
C      WRITE (*,*) -NCASE, NPFLKA, NSTMAX, SNGL (TKESUM),
C     &                SNGL (WEIPRI)
*  +-------------------------------------------------------------------*
*  |  (Radioactive) isotope: it works only for 1 source particle on
*  |  the stack for the time being
      IF ( ILOFLK (NPFLKA) .GE. 100000 .AND. LRADDC (NPFLKA) ) THEN
         IARES  = MOD ( ILOFLK (NPFLKA), 100000  )  / 100
         IZRES  = MOD ( ILOFLK (NPFLKA), 10000000 ) / 100000
         IISRES = ILOFLK (NPFLKA) / 10000000
         IONID  = ILOFLK (NPFLKA)
C         WRITE (*,*) ( IONID,SNGL(-TKEFLK(I)),
C     &                    SNGL (WTFLK(I)), SNGL (XFLK (I)),
C     &                    SNGL (YFLK (I)), SNGL (ZFLK (I)),
C     &                    SNGL (TXFLK(I)), SNGL (TYFLK(I)),
C     &                    SNGL (TZFLK(I)), I = 1, NPFLKA )
*  |
*  +-------------------------------------------------------------------*
*  |  Patch for heavy ions: it works only for 1 source particle on
*  |  the stack for the time being
      ELSE IF ( ABS (ILOFLK (NPFLKA)) .GE. 10000 ) THEN
         IONID = ILOFLK (NPFLKA)
         CALL DCDION ( IONID )
C         WRITE (*,*) ( IONID,SNGL(TKEFLK(I)+AMNHEA(-IONID)),
C     &                    SNGL (WTFLK(I)), SNGL (XFLK (I)),
C     &                    SNGL (YFLK (I)), SNGL (ZFLK (I)),
C     &                    SNGL (TXFLK(I)), SNGL (TYFLK(I)),
C     &                    SNGL (TZFLK(I)), I = 1, NPFLKA )
*  |
*  +-------------------------------------------------------------------*
*  |  Patch for heavy ions: ???
      ELSE IF ( ILOFLK (NPFLKA) .LT. -6 ) THEN
C         WRITE (*,*) ( IONID,SNGL(TKEFLK(I)+AMNHEA(-ILOFLK(NPFLKA))),
C     &                    SNGL (WTFLK(I)), SNGL (XFLK (I)),
C     &                    SNGL (YFLK (I)), SNGL (ZFLK (I)),
C     &                    SNGL (TXFLK(I)), SNGL (TYFLK(I)),
C     &                    SNGL (TZFLK(I)), I = 1, NPFLKA )
*  |
*  +-------------------------------------------------------------------*
*  |
      ELSE
      WRITE (*,*)   'Particle:',ILOFLK(1),
     &               'generation:',LOFLK(1),
     &               'totalEng:', SNGL (TKEFLK(1)),
     &               'age:',AGESTK(1)
      WRITE (*,*)  'xyz : ',SNGL(XFLK(1)),SNGL(YFLK(1)), SNGL (ZFLK(1))
C         WRITE (*,*) ( ILOFLK(I), SNGL (TKEFLK(I)+AM(ILOFLK(I))),
C     &                    SNGL (WTFLK(I)), SNGL (XFLK (I)),
C     &                    SNGL (YFLK (I)), SNGL (ZFLK (I)),
C     &                    SNGL (TXFLK(I)), SNGL (TYFLK(I)),
C     &                    SNGL (TZFLK(I)), I = 1, NPFLKA )
      END IF
      WRITE (*,*) ''
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
         OPEN ( UNIT = IODRAW, FILE = FILNAM, STATUS = 'NEW', FORM =
     &          'FORMATTED' )
      END IF
* No output by default:
      WRITE (*,*) 'lidj USDRAW(',ICODE,')'
      WRITE (*,*)  NTRACK, MTRACK, 'Particle:',JTRACK,
     &               'generation:',LTRACK,
     &               'totalEng:', SNGL (ETRACK),
     &               'age:',ATRACK,NCASE,NCASES
      WRITE (*,*)  'xyz : ',SNGL (XSCO), SNGL (YSCO), SNGL (ZSCO)
      WRITE (*,*) ''
      RETURN
*=== End of subrutine Mgdraw ==========================================*
      END

