<?php
    include '../include/db_connect.php';

    $sql = "SELECT ID_IS, IPassport, IFName, ILName, IBirthday
            FROM `internet_provider`.`installer` 
            LEFT JOIN `internet_provider`.`invoice` USING(ID_IS)
            WHERE ID_IV IS NULL
            GROUP BY ID_IS;";

    try {
        $result = $pdo->query($sql);
    } catch(PDOException $e) {
        echo "Ошибка выполнения запроса: ".$e->getMessage();
        include 'out.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        $installers = $result->fetchAll();
    } else {
        echo "Такие монтажники отсутствуют!";
        include 'out.html';
        exit();
    }
?>

<html>
    <head> <title> Интернет провайдер </title> </head>
    
    <body bgcolor=silver>
        <h2> Сведения о монтажниках, не составивших ещё ни одной накладной. </h2> <br>
        <table border=1 width=80%>
            <tbody>
                <tr>
                    <td> Табельный номер </td>
                    <td> Паспорт (серия, номер) </td>
                    <td> Имя </td>
                    <td> Фамилия </td>
                    <td> Дата рождения </td>
                </tr>

                <?php foreach($installers as $installer): ?>
                <tr>
                    <td> <?php echo $installer['ID_IS']; ?> </td>
                    <td> <?php echo $installer['IPassport']; ?> </td>
                    <td> <?php echo $installer['IFName']; ?> </td>
                    <td> <?php echo $installer['ILName']; ?> </td>
                    <td> <?php echo $installer['IBirthday']; ?> </td>
                </tr>
                <?php endforeach ?>
            </tbody>
        </table> <br>

        <?php include 'out.html'; ?>
    </body>
</html>