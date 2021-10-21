set /p comentario=Comentario:
git add .
git commit -m "%comentario%"
git push origin main