<?php
    include '../include/db_connect.php';

    $sql = "SELECT * FROM `internet_provider`.`installer`
            WHERE IFDate = (Select MIN(IFDate) FROM `internet_provider`.`installer`);";

    try {
        $result = $pdo->query($sql);
    } catch(PDOException $e) {
        echo "Ошибка выполнения запроса: ".$e->getMessage();
        include 'out.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        $installer = $result->fetch();
    } else {
        echo "Такой монтажник отсутствует!";
        include 'out.html';
        exit();
    }
?>

<html>
    <head> <title> Интернет провайдер </title> </head>
    
    <body bgcolor=silver>
        <h2> Сведения о монтажнике, который работает в компании дольше всех остальных.</h2> <br>
        <table border=1 width=80%>
            <tbody>
                <tr>
                    <td> Табельный номер </td>
                    <td> Паспорт (серия, номер) </td>
                    <td> Имя </td>
                    <td> Фамилия </td>
                    <td> Отчество </td>
                    <td> Пол </td>
                    <td> Дата рождения </td>
                    <td> Адрес </td>
                    <td> Дата приёма на работу </td>
                </tr>

                <tr>
                    <td> <?php echo $installer['ID_IS']; ?> </td>
                    <td> <?php echo $installer['IPassport']; ?> </td>
                    <td> <?php echo $installer['IFName']; ?> </td>
                    <td> <?php echo $installer['ILName']; ?> </td>
                    <td> <?php echo $installer['IMName']; ?> </td>
                    <td> <?php echo $installer['ISex']; ?> </td>
                    <td> <?php echo $installer['IBirthday']; ?> </td>
                    <td> <?php echo $installer['IAddress']; ?> </td>
                    <td> <?php echo $installer['IFDate']; ?> </td>
                </tr>
            </tbody>
        </table> <br>

        <?php include 'out.html'; ?>
    </body>
</html>