import DynamicBar from '@/components/DynamicBar'
import React from 'react'
import Image from 'next/image'
import CreditCardForm from '@/components/CreditCardForm'
import ContactForm from '@/components/ContactForm'
import PriceDetails from '@/components/PriceDetails'
import CarReview from '@/components/CarReview'
import AddressForm from '@/components/AddressForm'

const Review = () => {
  return (
    <>
      <DynamicBar type="Review" />
      <div className="container mx-auto flex flex-col lg:flex-row gap-8 py-10">
        <div className="w-full lg:w-1/3">
          <CarReview />
          <PriceDetails />
        </div>
        <div className="w-full lg:w-2/3">
          <ContactForm />
          <CreditCardForm />
          <AddressForm />
          <div className="bg-white p-6 rounded-lg shadow-lg w-full mt-10">
            <div className="flex justify-between items-center mb-4">
              <h2 className="text-2xl font-bold">Total</h2>
              <span className="text-2xl font-bold">$628.62</span>
            </div>
            <a href="#" className="text-blue-600 underline mb-4 block">Price details</a>
            <div className="text-gray-700 text-sm mb-4">
              <p className="mb-4">IMPORTANT INFORMATION about your PREPAID reservation: prepaid rates are subject to the following cancellation and no-show fees. Please note that the cancellation fees listed below will never exceed the total prepaid amount:</p>
              <ul className="list-disc pl-5 space-y-2">
                <li>$200.00 for cancellations within 24 hours prior to pickup time: Cancellations within 24 hours prior to the scheduled pickup time will result in the collection of a $200.00 cancellation fee. The remaining prepaid amount in excess of $200.00 will be refunded.</li>
                <li>$100.00 for cancellations up to 24 hours prior to pickup time: Cancellations up to 24 hours prior to scheduled pickup time will result in the collection of a $100.00 cancellation fee. The remaining prepaid amount in excess of $100.00 will be refunded.</li>
                <li>No refund for No-Show: No refund will be issued in case of failure to pick up your vehicle (no-show) or cancellation after scheduled pickup time.</li>
                <li>No refund for unused rental days: No refunds or credits will be issued for unused rental days (late pick up or early return) once the vehicle is rented.</li>
              </ul>
            </div>
            <div className="mb-4 flex items-start">
              <input type="checkbox" id="agreement" className="form-checkbox mt-1 mr-2" />
              <label htmlFor="agreement" className="text-gray-700 text-sm">
                I have read and accept the <a href="#" className="text-blue-600 underline">rental information</a>, the <a href="#" className="text-blue-600 underline">terms and conditions</a>, and the <a href="#" className="text-blue-600 underline">privacy policy</a>, and I acknowledge that I am booking a prepaid rate, where the total rental price is immediately charged to the credit or debit card I provided. I am aware that certain <a href="#" className="text-blue-600 underline">driver requirements</a> (e.g. age), <a href="#" className="text-blue-600 underline">payment requirements</a> (e.g. debit cards, security hold/deposit), and <a href="#" className="text-blue-600 underline">territorial restrictions</a> apply.
              </label>
            </div>
            <button className="w-full bg-blue-500 text-white py-3 rounded-lg font-bold">
              Pay and Book
            </button>
          </div>
        </div>
      </div>
    </>
  )
}

export default Review