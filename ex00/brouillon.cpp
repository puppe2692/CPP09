	{
		while (std::getline(infile, line))
		{
			std::istringstream stream(line);
			std::string dateStr, floatPart;

			std::getline(stream, dateStr, ',');
			std::getline(stream, floatPart);

			std::cout << "Date : " << dateStr << ", Float : " << floatPart << std::endl;
		}
	}




		else
	{
		while (std::getline(infile, line))
		{
			std::istringstream stream(line);
			std::string dateStr;
			float value;
			char comma;

			stream >> dateStr >> comma >> value;
			this->_csvData[dateStr] = value;
		}
	}
	for (const auto& entry : this->_csvData) {
        std::cout << "Date: " << entry.first << "/ Value: " << entry.second << std::endl;
    }