<?php
$servername = "localhost";
$username = "root";
$password = "toor";


// Creating a connection
$conn = new mysqli($servername, $username, $password);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
// Creating a database named HCALL
$sql = "CREATE DATABASE CHAL";
if ($conn->query($sql) === TRUE) {
    echo "Database created successfully with the name CHAL"."<br>";
} else {
    echo "Error creating database: " . $conn->error;
}
//Select db
$sql = "use CHAL";

if ($conn->query($sql) === TRUE) {
    echo "Successfully selected CHAL"."<br>";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}



//Inserting data
$sql = "CREATE TABLE chal (user varchar(20),pw varchar(30))";
if ($conn->query($sql) === TRUE) {
    echo "Table Chal created successfully"."<br>";
} else {
    echo "Error creating table: " . $conn->error;
}

$sql = "INSERT INTO chal VALUES ('abcdefg','32648215')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully"."<br>";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}


$sql = "INSERT INTO chal VALUES ('admin','17292115')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully"."<br>";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$sql = "INSERT INTO chal VALUES ('guest','25479640')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully"."<br>";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

// closing connection
$conn->close();
?>
