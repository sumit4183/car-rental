"use client"

import Equipment from '@/components/Equipment'
import PackageCard from '@/components/PackageCard'
import Protection from '@/components/Protection'
import { packages } from '@/constants'
import { useRouter } from 'next/navigation'
import router from 'next/router'
import React, { useState } from 'react'

const Options = () => {
  const [activeTab, setActiveTab] = useState<string | null>(null);

  const handleBackClick = () => {
    setActiveTab(null);
  };

  const renderButtons = () => (
    <div className="flex space-x-4">
      <button
        onClick={() => setActiveTab('Protection')}
        className={`flex items-center py-2 px-4 rounded ${activeTab === 'Protection' ? 'border-b-2 border-blue-500 text-blue-500' : 'text-gray-500'}`}
      >
        <span className="mr-2">🚨</span> {/* Replace with actual icon */}
        Protection & Coverages
      </button>
      <button
        onClick={() => setActiveTab('Equipment')}
        className={`flex items-center py-2 px-4 rounded ${activeTab === 'Equipment' ? 'border-b-2 border-blue-500 text-blue-500' : 'text-gray-500'}`}
      >
        <span className="mr-2">📡</span> {/* Replace with actual icon */}
        Equipment & Services
      </button>
    </div>
  );
  
  return (
    <div className="bg-gray-100">
      <div className="bg-white py-4 border-t-2 border-b-2">
        <div className="container mx-auto flex items-center justify-between px-4">
          <div className="flex items-end">
            {renderButtons()}
          </div>
          <div className="flex items-center">
            <button className="bg-blue-500 text-white py-2 px-4 rounded">
              Continue to Review
            </button>
          </div>
        </div>
      </div>
      { activeTab === null ? (
        <div className="container mx-auto p-4">
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-4">
            {packages.map((pkg) => (
              <PackageCard
                key={pkg.title}
                title={pkg.title}
                benefits={pkg.benefits}
                originalPrice={pkg.originalPrice}
                discountedPrice={pkg.discountedPrice}
                savings={pkg.savings}
              />
            ))}
          </div>
        </div>
      ) : activeTab === 'Protection' ? (
        <Protection onBack={handleBackClick} />
      ) : (
        <Equipment onBack={handleBackClick} />
      )}
    </div>
  )
}

export default Options