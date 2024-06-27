import React from 'react'

const ContactForm = () => {
  return (
    <div className="bg-white p-6 rounded-lg shadow-lg w-full">
      <h2 className="text-xl font-bold mb-4">Contact Details</h2>
      <form>
        <div className="mb-4">
          <label className="block text-sm font-bold mb-2" htmlFor="firstName">First Name*</label>
          <input type="text" id="firstName" className="w-full p-2 border rounded" />
        </div>
        <div className="mb-4">
          <label className="block text-sm font-bold mb-2" htmlFor="lastName">Last Name*</label>
          <input type="text" id="lastName" className="w-full p-2 border rounded" />
        </div>
        <div className="mb-4">
          <label className="block text-sm font-bold mb-2" htmlFor="phoneNumber">Phone Number*</label>
          <div className="flex">
            <select className="p-2 border rounded-l">
              <option value="+1">🇺🇸 +1</option>
              {/* Add more options as needed */}
            </select>
            <input type="text" id="phoneNumber" className="w-full p-2 border rounded-r" />
          </div>
        </div>
        <div className="mb-4">
          <label className="block text-sm font-bold mb-2" htmlFor="email">Email Address*</label>
          <input type="email" id="email" className="w-full p-2 border rounded" />
        </div>
      </form>
    </div>
  )
}

export default ContactForm