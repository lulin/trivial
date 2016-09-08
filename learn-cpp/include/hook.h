#ifndef __HOOK_H__
#define __HOOK_H__
//If you are using gtest, please add -DGTEST to your gcc/g++ option.
//This will give a gtest error if anything is wrong.


//set_global_hook can mock function globally. The mocked function can not be reverted.
//Usually, this API can be called in SetUpTestCase function of a test suite
//Example: set_global_hook((void*)&OrmSocket::connectServer,(void*)OrmSocket_connectServer_stub);
//Return true if success
bool set_global_hook(void *to_mock_func, void *mock_func);

//init_local_hook is to initialize and clean local hook buffer.
//It can be called in SetUpTestCase function of a test suite, or in SetUp function of each test case.
void init_local_hook();

//set_local_hook is to mock function locally or temporarily. It can be reverted by using un_local_hook.
//Example: set_local_hook((void*)&OrmSocket::connectServer,(void*)OrmSocket_connectServer_stub);
//Returned value indicates the index in local buffer (-1 means error)
int set_local_hook(void *to_mock_func, void *mock_func);

//un_local_hook is to unmock function which is mocked with set_local_hook.
//Example: un_local_hook((void*)&OrmSocket::connectServer);
//Return true if success
bool un_local_hook(void *to_mock_func);

//check_local_hook checks if local hook buffer is empty.
//Usually, this API is used in TearDown function of each test case to ensure if all local mocked functions are released.
//Return the total number of local mocked functions.
int check_local_hook();


#endif
