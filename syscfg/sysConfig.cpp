#include "sysConfig.h"
#include "cfgReader.h"
#include "../global/config.h"
#include "../logger/logger.h"

CSysConfig CSysConfig::m_instance;

CSysConfig::CSysConfig()
{
}


CSysConfig::~CSysConfig()
{
}

CSysConfig& CSysConfig::instance()
{
	return m_instance;
}

bool CSysConfig::loadConfig()
{
	CCfgReader reader(CONF_FILE);

	//读取http端口配置
	if (!reader.getIntValue("httpsvr.port", m_instance.m_httpConfig.m_httpPort))
	{
		CLogger::instance()->write_log(LOG_LEVEL_ERR, "读取http服务器端口配置失败");
		return false;
	}

	//读取数据库用户名
	if(!reader.getStringValue("database.username", m_instance.m_dbConfig.m_username))
	{
		CLogger::instance()->write_log(LOG_LEVEL_ERR, "读取数据库用户名配置失败");
		return false;
	}
	//读取数据库密码
	if (!reader.getStringValue("database.password", m_instance.m_dbConfig.m_password))
	{
		CLogger::instance()->write_log(LOG_LEVEL_ERR, "读取数据库密码配置失败");
		return false;
	}
	//读取数据库连接字符串
	if (!reader.getStringValue("database.connection", m_instance.m_dbConfig.m_connection))
	{
		CLogger::instance()->write_log(LOG_LEVEL_ERR, "读取数据库连接字符串置失败");
		return false;
	}
	//读取业务处理线程个数
	if (!reader.getIntValue("process.threadNum", m_instance.m_processConfig.m_threadNum))
	{
		CLogger::instance()->write_log(LOG_LEVEL_ERR, "读取业务处理线程数配置失败");
		return false;
	}
	//读取默认库ID
	if (!reader.getStringValue("process.defaultGroupId", m_instance.m_processConfig.m_defaultGroupId))
	{
		CLogger::instance()->write_log(LOG_LEVEL_ERR, "读取默认库ID配置失败");
		return false;
	}

	return true;
}
