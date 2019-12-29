#include "worker.h"

void TaskLoRaMsgProcessor(void* param)
{
  static_cast<LoRaMsgProcessor*>(param)->processMsgs();
}

void LoRaMsgProcessor::enqueue(LoRaMessage const& msg)
{
  xQueueSend(loRaMessages, &msg, portMAX_DELAY);
}

void LoRaMsgProcessor::processMsgs()
{
  LoRaMessage msg;
  for (;;)
  {
    xQueueReceive(loRaMessages, &msg, portMAX_DELAY);
    Serial.print("Message: ");
    for (size_t i = 0; i < msg.len; i++)
    {
      Serial.print(static_cast<char>(msg.buf[i]));
    }
    Serial.println();
  }
}