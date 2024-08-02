################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Core/Src/usbd_conf_template.c \
../Core/Core/Src/usbd_core.c \
../Core/Core/Src/usbd_ctlreq.c \
../Core/Core/Src/usbd_ioreq.c 

OBJS += \
./Core/Core/Src/usbd_conf_template.o \
./Core/Core/Src/usbd_core.o \
./Core/Core/Src/usbd_ctlreq.o \
./Core/Core/Src/usbd_ioreq.o 

C_DEPS += \
./Core/Core/Src/usbd_conf_template.d \
./Core/Core/Src/usbd_core.d \
./Core/Core/Src/usbd_ctlreq.d \
./Core/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Core/Src/%.o Core/Core/Src/%.su: ../Core/Core/Src/%.c Core/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../LWIP/App -I../LWIP/Target -I../Core/Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -I/WEBstm32/USB_DEVICE/STM32_USB_Device_Library/Class/CDC -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Core-2f-Src

clean-Core-2f-Core-2f-Src:
	-$(RM) ./Core/Core/Src/usbd_conf_template.d ./Core/Core/Src/usbd_conf_template.o ./Core/Core/Src/usbd_conf_template.su ./Core/Core/Src/usbd_core.d ./Core/Core/Src/usbd_core.o ./Core/Core/Src/usbd_core.su ./Core/Core/Src/usbd_ctlreq.d ./Core/Core/Src/usbd_ctlreq.o ./Core/Core/Src/usbd_ctlreq.su ./Core/Core/Src/usbd_ioreq.d ./Core/Core/Src/usbd_ioreq.o ./Core/Core/Src/usbd_ioreq.su

.PHONY: clean-Core-2f-Core-2f-Src

