float PCalculate(float currentHeat, float targetHeat, float range){
	float error = targetHeat - currentHeat;
	if(error > 0 && range/20<error){
		return 100;
	}
	else if(error > 0 && range/20>=error){ 
		return targetHeat * 8 -230;
	}
	else if(error < 0){
		return -100;
	}
 else if(error==0){
    return targetHeat * 8 -230;
 }
}

