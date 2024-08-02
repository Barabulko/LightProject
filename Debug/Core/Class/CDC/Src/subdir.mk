################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Class/CDC/Src/usbd_cdc.c \
../Core/Class/CDC/Src/usbd_cdc_if_template.c 

OBJS += \
./Core/Class/CDC/Src/usbd_cdc.o \
./Core/Class/CDC/Src/usbd_cdc_if_template.o 

C_DEPS += \
./Core/Class/CDC/Src/usbd_cdc.d \
./Core/Class/CDC/Src/usbd_cdc_if_template.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Class/CDC/Src/%.o Core/Class/CDC/Src/%.su: ../Core/Class/CDC/Src/%.c Core/Class/CDC/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../LWIP/App -I../LWIP/Target -I../Core/Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -I/WEBstm32/USB_DEVICE/STM32_USB_Device_Library/Class/CDC -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Class-2f-CDC-2f-Src

clean-Core-2f-Class-2f-CDC-2f-Src:
	-$(RM) ./Core/Class/CDC/Src/usbd_cdc.d ./Core/Class/CDC/Src/usbd_cdc.o ./Core/Class/CDC/Src/usbd_cdc.su ./Core/Class/CDC/Src/usbd_cdc_if_template.d ./Core/Class/CDC/Src/usbd_cdc_if_template.o ./Core/Class/CDC/Src/usbd_cdc_if_template.su

.PHONY: clean-Core-2f-Class-2f-CDC-2f-Src

