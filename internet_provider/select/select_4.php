<?php
    include '../include/db_connect.php';

    $sql = "SELECT ID_IS, IPassport, IFName, ILName, IBirthday, IAllCost
            FROM `internet_provider`.`invoice` 
            JOIN `internet_provider`.`installer` USING(ID_IS)
            WHERE YEAR(IDate) = 2017 AND IAllCost = (SELECT MAX(IAllCost) 
                FROM `internet_provider`.`invoice`)
            GROUP BY ID_IS;";

    try {
        $result = $pdo->query($sql);
    } catch(PDOException $e) {
        echo "������ ���������� �������: ".$e->getMessage();
        include 'out.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        $installer = $result->fetch();
    } else {
        echo "����� ��������� �����������!";
        include 'out.html';
        exit();
    }
?>

<html>
    <head> <title> �������� ��������� </title> </head>
    
    <body bgcolor=silver>
        <h2> �������� � ����������, ���������� ����� ������� ��������� � 2017 ����. </h2> <br>
        <table border=1 width=80%>
            <tbody>
                <tr>
                    <td> ��������� ����� </td>
                    <td> ������� (�����, �����) </td>
                    <td> ��� </td>
                    <td> ������� </td>
                    <td> ���� �������� </td>
                    <td> ��������� ������ �� ��������� </td>
                </tr>

                <tr>
                    <td> <?php echo $installer['ID_IS']; ?> </td>
                    <td> <?php echo $installer['IPassport']; ?> </td>
                    <td> <?php echo $installer['IFName']; ?> </td>
                    <td> <?php echo $installer['ILName']; ?> </td>
                    <td> <?php echo $installer['IBirthday']; ?> </td>
                    <td> <?php echo $installer['IAllCost']; ?> </td>
                </tr>
            </tbody>
        </table> <br>

        <?php include 'out.html'; ?>
    </body>
</html>