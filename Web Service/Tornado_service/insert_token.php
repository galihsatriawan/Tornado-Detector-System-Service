
<?php
include 'database_handler.php';
if($_SERVER['REQUEST_METHOD'] == 'POST'){
// if(true){
	
	$respon = array();
	 
	$token = $_POST['token'];
	// $token= "oke";
	$fields = array("token");
	$values = array($token);
	insert_data("tb_mst_token",$fields,$values);
	$respon['Pesan']= "Berhasil"." ".$token;
	echo json_encode($respon);
	
}else{

		$respon["status"] = "ok";
		$respon["json_api_version"]="0.0.1";
		echo json_encode($respon);
}
?>