PG3400 - Hjemmeeksamen - Reversi Console Game

Mappen HomeExam inneholder filene: board.c, board.h og Makefile.

All funksjonalitet er laget med funksjoner som finnes i board.c.
 
- Først settes brettet til utgangsposisjon.

- Så sjekkes det om spillerens trekk er gyldig.
	
- Brettet blir skrevet ut.

- Spiller gjør et trekk, det sjekkes i alle retninger der det er mulig for spiller å sette brikken sin.

- Deretter sjekkes hvilken spiller som har fått flest brikker på brettet. Når hele brettet blir fylt opp, returneres vinneren eller uavgjort basert på antall brikker.

- Starter spillet. Tar input fra spiller med tanke på hvor man skal plassere "brikken". En kan velge posisjon ved å skrive koordinater på følgende måter for eks. (B3), (b 3), (B,3). Input blir sjekket hvis det er skrevet på riktig måte ved hjelp av if statements slik at bruker ikke vil kunne sette en brikke utenfor brettet. Hvis det skrives ugyldig input, får en beskjed om at input ikke er gyldig og må gi nye koordinater. Det sjekkes også for både korrekte og feil plasseringer av brikken. Dersom det er korrekt legges brikken til og brettet oppdateres, hvis ikke får spiller beskjed om å plassere det et annet sted.

Hvert trekk blir lagret i en fil.
Jeg har laget en "Makefile" fil. Jeg var ikke på den siste forelesningen når det var snakk om det og er litt usikker på kravet for å lage en makefile. Men jeg har sett på nett eksempler på det så man kan tydeligvis lage den på flere måter.


