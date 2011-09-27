Bulkremover este un program creat pentru a sterge texte ce se repeta in diferite fisiere.
Programul preia ca si parametri adresa unui fisier care contine textul (pe cate o linie),
pe care utilizatorul doreste sa il stearga, iar al 2-lea parametru adresa catre folderul in care
sunt salvate fisierele pe care doreste utilizatorul sa le editeze.
Programul este facut utilizand librariile boost(http://www.boost.org/)
Programul este eliberat sub liceenta GPL.
Pentru a fi compilat este necesara linkeditarea urmatoarelor librarii:
- libboost_system-mgw44-mt.lib
- libboost_filesystem-mgw44-mt.lib
Codul ar trebuii sa fie in mare parte cross platform dar este necesara compilarea
celor 2 librarii pentru distributia utilizata.
Este posibil ca numele sa varieze acestea fiind librariile pentru Windows.
