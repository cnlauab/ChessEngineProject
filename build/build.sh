#! /bin/bash
makePath=/Users/francis3245/Documents/workspace/C++/ChessEngineProject/ChessEngineProject/build
copyPath=/Users/francis3245/Documents/workspace/lichess-bot-master/engines/build

echo "Building ChessEngineProject"
cd $makePath
make
cp $makePath/ChessEngineProject $copyPath/ChessEngineProject
echo "Finished Building"