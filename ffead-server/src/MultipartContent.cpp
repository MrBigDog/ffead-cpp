/*
 * MultipartContent.cpp
 *
 *  Created on: 28-Apr-2013
 *      Author: sumeetc
 */

#include "MultipartContent.h"

string MultipartContent::VALID_HEADERS = ",content-id,content-type,content-disposition,content-transfer-encoding,content-location,content-base,";

string MultipartContent::ContentId = "Content-Id";
string MultipartContent::ContentDisposition = "Content-Disposition";
string MultipartContent::ContentTransferEncoding = "Content-Transfer-Encoding";
string MultipartContent::ContentLocation = "Content-Location";
string MultipartContent::ContentBase = "Content-Base";
string MultipartContent::ContentLength = "Content-Length";
string MultipartContent::ContentMD5 = "Content-MD5";
string MultipartContent::ContentType =	"Content-Type";

MultipartContent::MultipartContent() {
	logger = Logger::getLogger("MultipartContent");
}

MultipartContent::MultipartContent(vector<string> headers)
{
	logger = Logger::getLogger("MultipartContent");
	if(headers.size()!=0)
	{
		for(unsigned int i=0;i<headers.size();i++)
		{
			vector<string> temp;
			if((headers.at(i)=="\r" || headers.at(i)==""|| headers.at(i)=="\r\n"))
			{
				continue;
			}
			StringUtil::split(temp, headers.at(i), (": "));
			if(temp.size()>1)
			{
				StringUtil::replaceFirst(temp.at(1), "\r", "");
				if(temp.at(0).find("Content-Disposition")!=string::npos)
				{
					vector<string> parmdef;
					StringUtil::split(parmdef, temp.at(1), (";"));
					for(unsigned k=0;k<parmdef.size();k++)
					{
						if(parmdef.at(k)!="" && parmdef.at(k).find("=")!=string::npos)
						{
							size_t stpd = parmdef.at(k).find_first_not_of(" ");
							size_t enpd = parmdef.at(k).find_last_not_of(" ");
							string propert = parmdef.at(k).substr(stpd,enpd-stpd+1);
							vector<string> proplr;
							StringUtil::split(proplr, propert, ("="));
							if(proplr.size()==2)
							{
								if(proplr.at(0)=="name" && proplr.at(1)!="\"\"")
								{
									string key = proplr.at(1);
									key = key.substr(key.find_first_not_of("\""),key.find_last_not_of("\"")-key.find_first_not_of("\"")+1);
									key = CryptoHandler::urlDecode(key);
									name = key;
								}
								else if(proplr.at(0)=="filename" && proplr.at(1)!="\"\"")
								{
									string fna = proplr.at(1);
									fna = fna.substr(fna.find_first_not_of("\""),fna.find_last_not_of("\"")-fna.find_first_not_of("\"")+1);
									fna = CryptoHandler::urlDecode(fna);
									fileName = fna;
								}
							}
						}
					}
				}
				addHeaderValue(temp.at(0), temp.at(1));
			}
		}
	}
}

MultipartContent::~MultipartContent() {
}

string MultipartContent::getContent() const {
	return content;
}

void MultipartContent::setContent(string content) {
	this->content = content;
}

string MultipartContent::getFileName() const {
	return fileName;
}

void MultipartContent::setFileName(string fileName) {
	this->fileName = fileName;
}

map<string, string> MultipartContent::getHeaders() const {
	return headers;
}

string MultipartContent::getTempFileName() const {
	return tempFileName;
}

void MultipartContent::setTempFileName(string tempFileName) {
	this->tempFileName = tempFileName;
}

void MultipartContent::addHeaderValue(string header, string value)
{
	header = StringUtil::camelCasedCopy(header, "-");
	if(header!="")
	{
		if(VALID_HEADERS.find(","+StringUtil::toLowerCopy(header)+",")!=string::npos)
		{
			headers[header] = value;
		}
		else
		{
			vector<string> matres = RegexUtil::search(header, "^[a-zA-Z]+[-|a-zA-Z]+[a-zA-Z]*[a-zA-Z]$");
			if(matres.size()==0)
			{
				cout << ("Invalid Header string " + header) << endl;
				return;
			}
			headers[header] = value;
		}
	}
}

bool MultipartContent::isHeaderValue(string header, string value, bool ignoreCase)
{
	header = StringUtil::camelCasedCopy(header, "-");
	return header!="" && headers.find(header)!=headers.end()
			&& (headers[header]==value ||
					(ignoreCase && StringUtil::toLowerCopy(headers[header])==StringUtil::toLowerCopy(value)));
}

string MultipartContent::getName() const {
	return name;
}

void MultipartContent::setName(string name) {
	this->name = name;
}

string MultipartContent::getHeader(string header)
{
	if(headers.find(header)!=headers.end())
	{
		return headers[header];
	}
	return "";
}
