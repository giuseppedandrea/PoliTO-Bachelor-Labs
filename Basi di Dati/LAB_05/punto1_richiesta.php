<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 1 - Richiesta</title>
    </head>
    <body>
        <h1>Inserimento nuovo corso</h1>
        <form action="punto1_risultato.php" method="post">
            <p>Dati del nuovo corso da inserire</p>
            <table>
                <tr>
                    <td>Codice:</td>
                    <td><input type="text" size="10" maxlength="10" name="codice_corso"></td>
                </tr>
                <tr>
                    <td>Nome:</td>
                    <td><input type="text" size="50" maxlength="50" name="nome_corso"></td>
                </tr>
                <tr>
                    <td>Tipo:</td>
                    <td><input type="text" size="50" maxlength="50" name="tipo_corso"></td>
                </tr>
                <tr>
                    <td>Livello:</td>
                    <td><input type="text" size="10" maxlength="10" name="livello_corso"></td>
                </tr>
            </table>
            <br>
            <input type="submit" value="Inserisci">
        </form>
    </body>
</html>
