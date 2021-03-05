<?php
    include '../include/db_connect.php';

    $sql = "SELECT * FROM `internet_provider`.`installer`
            WHERE IFDate = (Select MIN(IFDate) FROM `internet_provider`.`installer`);";

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
        <h2> �������� � ����������, ������� �������� � �������� ������ ���� ���������.</h2> <br>
        <table border=1 width=80%>
            <tbody>
                <tr>
                    <td> ��������� ����� </td>
                    <td> ������� (�����, �����) </td>
                    <td> ��� </td>
                    <td> ������� </td>
                    <td> �������� </td>
                    <td> ��� </td>
                    <td> ���� �������� </td>
                    <td> ����� </td>
                    <td> ���� ����� �� ������ </td>
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