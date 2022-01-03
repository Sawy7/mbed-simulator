#include "mbed.h"
#include "NetworkInterface.h"
#include "UDPSocket.h"

uint32_t ntohl(uint32_t const net) {
  uint8_t data[4] = {};
  memcpy(&data, &net, sizeof(data));

  return ((uint32_t) data[3] << 0)
     | ((uint32_t) data[2] << 8)
     | ((uint32_t) data[1] << 16)
     | ((uint32_t) data[0] << 24);
}

namespace VirtualRtc
{
  // mbed simulator time functions are not working for some reason
  // so this is a workaround to be able to use time.
  time_t rtcTime;
  Ticker ticker;
  static void _set_time(time_t t)
  { 
    rtcTime = t; 
  };
  static void _inc_time() 
  { 
    rtcTime++; 
  };
  static time_t _get_time(void) 
  { 
    return rtcTime; 
  };
  void init()
  {
    ticker.attach(&_inc_time, 1.0f);
    attach_rtc(&_get_time, &_set_time, NULL, NULL);
  }
  void init(time_t t)
  {
    _set_time(t);
    init();
  }
};

int main() {
  printf("Time protocol example\n");

  NetworkInterface *net = NetworkInterface::get_default_instance();
  if(net->connect() != NSAPI_ERROR_OK) {
    printf("Error connecting\n");
    return -1;
  }

  // Show the network address
  const char *ip = net->get_ip_address();
  printf("IP address is: %s\n", ip ? ip : "No IP");
  
  VirtualRtc::init();

  while (1) {
    UDPSocket sock(net);

    nsapi_size_or_error_t n;

    char send_buffer[] = "time";
    if((n = sock.sendto("time.nist.gov", 37, send_buffer, sizeof(send_buffer))) < NSAPI_ERROR_OK) {
      printf("Error sending data (%d)\n", n);
      wait_ms(10000); continue;
    }

    uint32_t recv_buffer;
    n = sock.recvfrom(NULL, &recv_buffer, sizeof(recv_buffer));
    if (n != sizeof(recv_buffer)) {
      printf("recvfrom failed (%d)\n", n);
      wait_ms(10000); continue;
    }

    unsigned long epoch = ntohl(recv_buffer) - 2208988800ull;  // 1900-1970
    printf("\nCurrent time from NTP: %s", ctime(( const time_t* )&epoch));
    
    set_time(epoch);

    sock.close();

    for(int i=0; i<10; i++)
    {
      wait_ms(1000);
      epoch = time(NULL);
      printf("\nCurrent time from RTC: %s", ctime(( const time_t* )&epoch));
    }
  }
}
