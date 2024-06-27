import React from 'react'
import Image from 'next/image';

const CarReview = () => {
  return (
    <div className="bg-white p-6 rounded-lg shadow-lg w-full">
      <div className="flex mb-4">
        <Image 
          src="/car.jpg" 
          alt="Car Image" 
          height={100}
          width={100}
          className="rounded" 
        />
        <div className="ml-4">
          <h3 className="text-xl font-bold">Midsize (Toyota RAV4)</h3>
          <p className="text-gray-600">or similar | SUV</p>
          <p className="text-gray-600">4 rental days</p>
        </div>
      </div>
      <div className="mb-4">
        <div className="flex items-center mb-2">
          <div>
            <p className="font-bold">Pickup</p>
            <p>Orlando Int Airport</p>
            <p>Thu, Jun 27, 2024 | 12:30 PM</p>
          </div>
        </div>
        <div className="flex items-center">
          <div>
            <p className="font-bold">Return</p>
            <p>Orlando Int Airport</p>
            <p>Mon, Jul 01, 2024 | 08:30 AM</p>
          </div>
        </div>
      </div>
      <hr className="border-gray-300" />
      <div className="p-4">
        <h4 className="font-bold mb-2">Your booking overview:</h4>
        <ul className="list-disc pl-5 space-y-1 text-gray-700">
          <li>24/7 Roadside Assistance Hotline</li>
          <li>Unlimited miles</li>
          <li>Cover The Car - No deductible</li>
          <li>GPS</li>
          <li>Connect</li>
          <li>Booking option: Best price - Pay now, cancel and rebook for a fee</li>
        </ul>
      </div>
    </div>
  )
}

export default CarReview