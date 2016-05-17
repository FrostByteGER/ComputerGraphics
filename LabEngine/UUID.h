#pragma once

class LEUUID{

	private:
		static uint32_t uuid;
	public:
		static uint32_t generateUUID(){
			return ++uuid;
		}
};

uint32_t LEUUID::uuid = 0;
