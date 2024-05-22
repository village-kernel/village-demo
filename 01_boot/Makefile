all:
	cd boot && make && cd ..
	cd app && make && cd ..
	dd if=/dev/zero               of=village-os.img bs=512 count=2880
	dd if=boot/village-boot.bin   of=village-os.img bs=512 seek=0 conv=notrunc
	dd if=app/village-kernel.bin  of=village-os.img bs=512 seek=1 conv=notrunc

clean:
	cd boot && make clean && cd ..
	cd app && make clean && cd ..
