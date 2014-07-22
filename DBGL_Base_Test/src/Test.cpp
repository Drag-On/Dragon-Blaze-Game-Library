#include <cute_runner.h>
#include <cute_suite.h>
#include <cute_test.h>
#include <cute_xml_file.h>
#include <ide_listener.h>
#include <xml_listener.h>
#include <vector>

#include "DBGL/DBGL_Base_Config.h"
#include "DBGL/System/Log/Log.h"

int testLog();
int testUtility();
int testVector2();
int testVector3();
int testVector4();
int testVector();
int testMatrix2x2();
int testMatrix3x3();
int testMatrix4x4();
int testMatrix();
int testQuaternion();
int testProperties();
int testBitmask();
int testKdTree();
int testHyperrectangle();
int testSceneGraph();

void runAllTests(int argc, char const *argv[]){
	cute::suite s{};
	//TODO add your test here
	s.push_back(CUTE(testLog));
	s.push_back(CUTE(testUtility));
	s.push_back(CUTE(testVector2));
	s.push_back(CUTE(testVector3));
	s.push_back(CUTE(testVector4));
	s.push_back(CUTE(testVector));
	s.push_back(CUTE(testMatrix2x2));
	s.push_back(CUTE(testMatrix3x3));
	s.push_back(CUTE(testMatrix4x4));
	s.push_back(CUTE(testMatrix));
	s.push_back(CUTE(testQuaternion));
	s.push_back(CUTE(testProperties));
	s.push_back(CUTE(testBitmask));
	s.push_back(CUTE(testKdTree));
	s.push_back(CUTE(testHyperrectangle));
	s.push_back(CUTE(testSceneGraph));
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
	LOG.setLogLevel(dbgl::Log::Level::DBG);
	LOG.info("DBGL Version %", DBGL_VERSION_FULL);

    runAllTests(argc,argv);

	LOG.info("Tests done!");
    return 0;
}



