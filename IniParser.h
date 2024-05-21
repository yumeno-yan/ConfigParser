#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>

class IniParser
{
public:
    void parser(const std::string &filename)
    {
        std::ifstream infile(filename);
        if (!infile)
        {
            std::cerr << "cannot open file!\n";
            return;
        }
        std::string str;
        std::string cur_section;
        while (getline(infile, str))
        {
            trim(str);
            // 略过空行，注释也略过
            if (str.empty() || str[0] == '#' || str[0] == ';')
                continue;
            std::string::size_type position;
            position = str.find_last_of(']');
            // 进入这个分支说明当前是一个section
            if (str[0] == '[' && position != std::string::npos)
            {
                cur_section = str.substr(1, position - 1);
                data.emplace(cur_section, std::map<std::string, std::string>());
            } else // 否则就尝试识别为kv对
            {
                // 如果此时section为空则报错
                if (cur_section.empty())
                {
                    std::cerr << "syntax error!\n";
                    return;
                }
                position = str.find('=');
                if (position == std::string::npos)
                {
                    // 没找到说明语法错误
                    std::cerr << "syntax error!\n";
                    return;
                }
                std::string key = str.substr(0, position);
                std::string value = str.substr(position + 1);
                // 去除头尾的空格
                trim(key);
                trim(value);
                data[cur_section].emplace(make_pair(key, value));
            }
        }
        infile.close();
    }

    std::string get(const std::string &section, const std::string &option)
    {
        auto it_section = data.find(section);
        if (it_section == data.end())
            return "";
        auto iter = it_section->second.find(option);
        if (iter != it_section->second.end())
            return iter->second;
        return "";
    }

    std::vector<std::string> sections()
    {
        std::vector<std::string> ans;
        ans.reserve(data.size());
        for (const auto &it: data)
        {
            ans.emplace_back(it.first);
        }
        return ans;
    }

    std::map<std::string, std::string> items(const std::string &section)
    {
        auto it = data.find(section);
        if (it != data.end())
            return it->second;
        return {};
    }

private:
    // 去除头尾的空格和制表符
    void trim(std::string &str) const
    {
        auto start = str.find_first_not_of(" \t");
        auto end = str.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos)
        {
            str = str.substr(start, end - start + 1);
        } else
        {
            // 找不到说明这一行全是空格和制表符
            str.clear();
        }
    }

private:
    std::map<std::string, std::map<std::string, std::string>> data;
};