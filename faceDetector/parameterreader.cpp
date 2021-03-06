#include "parameterreader.h"

#include <QDebug>
#include <QStringList>

#include "configuration.h"
#include "utils.h"

ParameterReader::ParameterReader() : _input(stdin)
{
}

void ParameterReader::readParameters(){
	QString command;

	int cnt = 0;
    do{
		qDebug() << ">> ";
		if (_input.atEnd()) {
			command = "exit";
		} else {
			command = _input.readLine();
			if (command.isEmpty()) {
				if (++cnt == 3) {
					command = "exit";
				}
			}
		}
        chooseAction(command);

	} while(!command.startsWith("exit"));
}

void ParameterReader::chooseAction(QString command){

    Configuration cfg;

    QStringList parameters = command.split(QRegExp("\\s+"));

    if("test" == parameters.at(0)){

		if (parameters.size() == 5) {
			cfg._annSaveFile = parameters.at(1);
			cfg._annSaveFile2 = parameters.at(2);
			cfg._directory = parameters.at(3);
			cfg._outputDirectory = parameters.at(3);
			cfg._testThreshold = parameters.at(4).toFloat();
		} else {
			cfg._annSaveFile = parameters.at(1);
			cfg._annSaveFile2 = parameters.at(2);
			cfg._directory = parameters.at(3);
			cfg._outputDirectory = parameters.at(4);
			cfg._testThreshold = parameters.at(5).toFloat();
		}

		Utils::testNetwork(cfg);

    } else if("train" == parameters.at(0)){

        cfg._annSaveFile = parameters.at(1);
        cfg._dataFile = parameters.at(2);
        cfg._valDataFile = parameters.at(3);
        cfg._learningRate = parameters.at(4).toFloat();
        cfg._momentum = parameters.at(5).toFloat();

        Utils::trainNetwork(cfg);

	} else if("gen" == parameters.at(0)){

		cfg._dataFile = parameters.at(1);
		cfg._directory = parameters.at(2);

		Utils::prepareData(cfg);

    } else if("exit" == parameters.at(0)){

        return;

    } else{

        qDebug() << "Niewlasciwy parametr: " << parameters.at(0);
    }
}
