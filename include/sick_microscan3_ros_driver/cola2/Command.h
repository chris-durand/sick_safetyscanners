#pragma once

#include <sick_microscan3_ros_driver/datastructure/DataTypes.h>
#include <sick_microscan3_ros_driver/datastructure/PacketBuffer.h>

#include <sick_microscan3_ros_driver/data_processing/ReadWriteHelper.h>
#include <sick_microscan3_ros_driver/data_processing/ParseTCPPacket.h>

#include <boost/thread/mutex.hpp>

namespace sick {
namespace cola2 {

class Cola2Session;

class Command
{
public:
  Command(sick::cola2::Cola2Session& session, UINT16 commandType, UINT16 commandMode);


  void lockExecutionMutex();

  void constructTelegram(sick::datastructure::PacketBuffer::VectorBuffer& telegram) const;

  void processReplyBase(const sick::datastructure::PacketBuffer::VectorBuffer& packet);

  void waitForCompletion();

  UINT32 getSessionID() const;
  void setSessionID(const UINT32 &sessionID);


  bool wasSuccessful() const;


  UINT8 getCommandType() const;
  void setCommandType(const UINT8 &command_type);

  UINT8 getCommandMode() const;
  void setCommandMode(const UINT8 &command_mode);

  UINT16 getRequestID() const;
  void setRequestID(const UINT16 &requestID);

  std::vector<BYTE> getData() const;
  void setData(const std::vector<BYTE> &data);

protected:
  sick::cola2::Cola2Session& m_session;

private:
  boost::shared_ptr<sick::data_processing::ParseTCPPacket> m_tcp_parserPtr;
  boost::shared_ptr<sick::data_processing::ReadWriteHelper> m_writerPtr;


  virtual bool processReply() = 0;

  void addTelegramHeader(sick::datastructure::PacketBuffer::VectorBuffer& telegram) const;
  virtual void addTelegramData(sick::datastructure::PacketBuffer::VectorBuffer& telegram) const = 0;


  boost::mutex m_executionMutex;

  bool m_wasSuccessful;





  UINT8 m_command_type;
  UINT8 m_command_mode;
  UINT32 m_sessionID;
  UINT16 m_requestID;

  std::vector<BYTE> m_data;
};


}
}

