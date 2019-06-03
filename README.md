# Internship2019
In solutia data avem implementat un arbore de relatii intre persoane, echivalentul unei structuri organizationale. Informatia primara este predefinita intr-o variabila statica de tip lista. La rulare arborele construit ar trebui salvat intr-o baza de date locala de tip SQL. Solutia este incompleta. De asemenea, exista probleme de optimizare.
Cerintele de mai jos cauta sa acopere atat lipsurile de implementare cat si eventualele optimizari:
1.	Salvarea arborelui in baza de date.
2.	Gasiti toate nodurile care au parintele comun cu un nod cu nume dat.
3.	Gasiti eventuale optimizari in lucrul cu baza de date.
4.	In contextul limbajului C# exista posibilitatea de a folosi un sub-limbaj structurat pentru lucrul cu colectii (LINQ); de exemplu „Nodes.Where(...)...” sau „Nodes.Single...”. Gasiti eventuale probleme sau optimizari in lucrul cu colectii.
5.  (Optional)Din tree-ul obtinut din StaticNamesTreeReader().ConstructTree() obtineti o lista si sortati-o ascendent dupa TreeNode.Description.


Test pull request

Pentru a comite modificarile executati:

git checkout -b Nume.Prenume
git add .
git commit -m "ce vreti voi"
git push -u origin Nume.Prenume
