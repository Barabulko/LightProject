################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_DEVICE/CDC/Src/usbd_cdc.c \
../USB_DEVICE/CDC/Src/usbd_cdc_if_template.c 

OBJS += \
./USB_DEVICE/CDC/Src/usbd_cdc.o \
./USB_DEVICE/CDC/Src/usbd_cdc_if_template.o 

C_DEPS += \
./USB_DEVICE/CDC/Src/usbd_cdc.d \
./USB_DEVICE/CDC/Src/usbd_cdc_if_template.d 


# Each subdirectory must supply rules for building sources it contributes
USB_DEVICE/CDC/Src/%.o USB_DEVICE/CDC/Src/%.su USB_DEVICE/CDC/Src/%.cyclo: ../USB_DEVICE/CDC/Src/%.c USB_DEVICE/CDC/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I"C:/Users/practicant/Desktop/uvn(r)/USB_DEVICE/App" -I"C:/Users/practicant/Desktop/uvn(r)/USB_DEVICE/CDC/Inc" -I"C:/Users/practicant/Desktop/uvn(r)/USB_DEVICE/CDC/Src" -I"C:/Users/practicant/Desktop/uvn(r)/USB_DEVICE/Core/Inc" -I"C:/Users/practicant/Desktop/uvn(r)/USB_DEVICE/Core/Src" -I"C:/Users/practicant/Desktop/uvn(r)/USB_DEVICE/Target" -I../LWIP/App -I../LWIP/Target -I../Core/Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-USB_DEVICE-2f-CDC-2f-Src

clean-USB_DEVICE-2f-CDC-2f-Src:
	-$(RM) ./USB_DEVICE/CDC/Src/usbd_cdc.cyclo ./USB_DEVICE/CDC/Src/usbd_cdc.d ./USB_DEVICE/CDC/Src/usbd_cdc.o ./USB_DEVICE/CDC/Src/usbd_cdc.su ./USB_DEVICE/CDC/Src/usbd_cdc_if_template.cyclo ./USB_DEVICE/CDC/Src/usbd_cdc_if_template.d ./USB_DEVICE/CDC/Src/usbd_cdc_if_template.o ./USB_DEVICE/CDC/Src/usbd_cdc_if_template.su

.PHONY: clean-USB_DEVICE-2f-CDC-2f-Src
