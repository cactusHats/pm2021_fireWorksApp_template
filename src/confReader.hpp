//***********************************************************************************************************
//*	2021/04/28 �쐬�ҁF�k��
//* �O���t�@�C������L�[�ƃf�[�^��ǂݎ��
//* �f�[�^�̏������́C��؂蕶����=�Ƃ����ꍇ�͈ȉ��̂悤�ɋL�q����
//* KEY=value
//* 
//* 2021/05/18 char*�^�ɑΉ�
//***********************************************************************************************************



#ifndef _CONF_READER_H
#define _CONF_READER_H

#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

namespace conf {
    std::unordered_map<std::string, std::string> config_map; // �L�[�Ɨv�f���i�[

    // �i���K�\���́j��؂蕶���ݒ�D
    // �����͋�؂蕶���Ɏg���������������ł������OK�D�g�p�s�����i.|�j
    template <class... STR> std::string setSeparetor(STR ...sep) {
        std::string regex_separator = "";
        for (std::string i : std::initializer_list<std::string>{ sep... }) {
            regex_separator += i;
            regex_separator += '|';
        }
        regex_separator.erase(--regex_separator.end());
        return regex_separator;
    }

    // ������(string)����؂蕶���ŕ�������
    // ����(����������������, �����񃊃e�����\�L�̋�؂蕶��)
	// �Ⴆ��=�Ƌ󔒂���؂蕶���Ȃ� R"(=|\s)"
    std::vector<std::string> split(const std::string& str, const std::string& regex_separator) {
        std::vector<std::string> splited_str;
        std::regex rx(regex_separator);
        std::sregex_token_iterator it(str.begin(), str.end(), rx, -1);
        std::sregex_token_iterator end;
        while (it != end) splited_str.emplace_back(*it++);
        return splited_str;
    }

    // �ݒ�t�@�C������ǂݍ��񂾃L�[�Ɨv�f��ۑ�
    void setMap(std::unordered_map<std::string, std::string>& conf, std::ifstream& input_file, const std::string& regex_separator) {
        std::string row;
		conf.clear();
        while (std::getline(input_file, row)) {
            std::vector<std::string> splited_str = split(row, regex_separator);
            conf.emplace(splited_str[0], splited_str[1]);
        }
    }

    // �����ɃL�[������Ƃ��̒l���Ԃ��Ă���D�����ɂ���ĕԂ��^���ς��D
    // �Ή��^:string,char*,short,int,long,float,double,
    class readMap {
    public:
        readMap(std::string key) {
            if (config_map.find(key) == config_map.end()) _key = "DUMMY"; // �L�[�����݂��Ȃ��Ȃ�_�~�[�̃L�[�𐶐�
            else _key = key;
        }
        template<class T> operator T();

    private:
        std::string _key; // �����̓n�������s���������߁C��U�������ɑ������D
    };

    template<> readMap::operator std::string() {
        return config_map[_key];
    }

	template<> readMap::operator short() {
		int num;
		try { num = stoi(config_map[_key]); }
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			num = 0;
		}
		return static_cast<short>(num);
	}

    template<> readMap::operator int() {
        int num;
        try { num = stoi(config_map[_key]); }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            num = 0;
        }
        return num;
    }

    template<> readMap::operator long() {
        long num;
        try { num = stol(config_map[_key]); }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            num = 0;
        }
        return num;
    }

    template<> readMap::operator float() {
        float num;
        try { num = stof(config_map[_key]); }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            num = 0.f;
        }
        return num;
    }

    template<> readMap::operator double() {
        double num;
        try { num = stod(config_map[_key]); }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            num = 0.f;
        }
        return num;
    }

	template<> readMap::operator const char*() {
		return config_map[_key].c_str();
	}
}
#endif