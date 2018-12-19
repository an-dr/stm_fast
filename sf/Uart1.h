/*
 * author dongr
 *
 * To change this generated comment edit the template variable "comment":
 * Window > Preferences > C/C++ > Editor > Templates.
 */

#ifndef UART1_H_
#define UART1_H_

#include <stdint.h>
#include <string>
#include <math.h>
#include "stm32l1xx.h"
#include "stm32l1xx_hal_rcc.h"

using namespace std;

namespace sf
{

    /*
     *
     */
    class Uart1
    {
    private:
        uint32_t baudrate;
        uint8_t * rx_buff_p;
        bool Init();
        bool Pre_Init();
        bool Deinit();
        void SetBaudRate(uint32_t new_br);

    public:
        Uart1();
        Uart1(const uint32_t & spec_baudrate);
        Uart1(const uint32_t & spec_baudrate,
              const uint8_t * rx_buf,
              const uint32_t & buf_size);
        void IRQ(bool rx, bool tx);
        bool Send(const string & tx_str);
        bool Send(const uint8_t & tx);
        void Receive(string * rx_str);
        virtual ~Uart1();
    };

} /* namespace sf */

#endif /* UART1_H_ */
