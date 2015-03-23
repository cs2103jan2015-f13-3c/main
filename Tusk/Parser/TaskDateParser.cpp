#include "TaskDateParser.h"


TaskDateParser::TaskDateParser(std::string input){
	_dateParserInput = input;
}

TaskDateParser::TaskDateParser(void){
}

void TaskDateParser::setInput(std::string input){
	_dateParserInput = input;
}

void TaskDateParser::parse(){
	std::string dateStr;

	if(isDateInput()){
		dateStr = getDateStr();
		setDateType(dateStr);	
		setDate(dateStr);

	}
}

std::string TaskDateParser::getDateStr(){
	return getKeywordAfter(DATE_KEYWORD, _dateParserInput);
}

void TaskDateParser::setDateType(std::string dateStr){
	_containsDateType = DEFAULT_DATE;
	
	if(isFound(DATE_WITH_RANGE_KEY, dateStr)){
		_containsDateType = DATE_W_RANGE;
	}
}

void TaskDateParser::setDate(std::string dateStr){
	switch(_containsDateType){	
	
	case DEFAULT_DATE:
		_dateStart = dateStr.substr(0,10);
		_dateEnd = _dateStart; 
		break;	
	case DATE_W_RANGE:
		_dateStart = dateStr.substr(0,10);
		_dateEnd = dateStr.substr(11,21); 
		break;
		
	}
}

bool TaskDateParser::isDateInput(){
return(isFound(DATE_KEYWORD, _dateParserInput));
}

bool TaskDateParser::isFound(std::string keyword,std::string sentence){
	return sentence.find(keyword) != std::string::npos;
}	

std::string TaskDateParser::getKeywordAfter(std::string keyword, std::string sentence){
sentence = sentence.substr(sentence.find(keyword));
return sentence.substr(0,sentence.find(" "));
}

Date TaskDateParser::getDate(){
	return getDateStart();
}

Date TaskDateParser::getDateStart(){
	std::string dateStr = _dateStart;
	Date newDate;

	newDate.setDay(getNumber(dateStr));
	newDate.setMonth( getMonth(getNumber(dateStr)) );
	newDate.setYear(getNumber(dateStr));

	return newDate;
}

Date TaskDateParser::getDateEnd(){
	if(_containsDateType = DEFAULT_DATE){
		return getDateStart();
	}
	std::string dateStr = _dateEnd;
	Date newDate;
	newDate.setDay(getNumber(dateStr));
	newDate.setMonth( getMonth(getNumber(dateStr)) );
	newDate.setYear(getNumber(dateStr));

	return newDate;

}

int TaskDateParser::getNumber(std::string& date){
	std::string numberStr = date.substr(0,date.find(D_M_Y_KEY)); 
	date.erase(0, numberStr.length()+1);
	return atoi(numberStr.c_str());
}

Month TaskDateParser::getMonth(int month){
	switch(month){
	case 1:
		return JANUARY;
	case 2:
		return FEBRUARY;
	case 3:
		return MARCH;
	case 4:
		return APRIL;
	case 5:
		return MAY;
	case 6:
		return JUNE;
	case 7:
		return JULY;
	case 8:
		return AUGUST;
	case 9:
		return SEPTEMBER;
	case 10:
		return OCTOBER;
	case 11:
		return NOVEMBER;
	case 12:
		return DECEMBER;
	}

	return JANUARY;
}