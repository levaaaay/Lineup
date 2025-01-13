<template>
    <div class="registration">
      <div class="globalHeader">
        <h1>Registration</h1>
      </div>
      <div class="service-list">
        <div class="service-item" v-for="(service, index) in services" :key="index">
          <span>{{ service }}</span>
          <button class="edit-button">
            <img src="https://cdn-icons-png.flaticon.com/512/1827/1827933.png" alt="Edit" />
          </button>
        </div>
        <div class="add-service">
          <button @click="addNewService">+ Add New Service</button>
        </div>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    name: "registration",
    data() {
      return {
        services: [
          "Student-Driver's Permit",
          "New Driver's License (Non-Professional)",
          "Conductor's License",
        ],
      };
    },
    methods: {
      addNewService() {
        this.services.push("New Service");
      },
    },
  };
  </script>
  
  <style scoped>
  .registration {
    background-color: #E9ECEF;
    padding: 2rem;
  }
  
  .service-list {
    border-radius: 10px;
    padding: 1rem;
  }
  
  .service-item {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0.5rem 1rem;
    border: 1px solid #DEE2E6;
    border-radius: 5px;
    background: #f9f9f9;
  }
  
  .service-item span {
    font-size: 1rem;
  }
  
  .edit-button {
    background: none;
    border: none;
    cursor: pointer;
  }
  
  .edit-button img {
    width: 16px;
    height: 16px;
  }
  
  .add-service {
    text-align: center;
    margin-top: 1rem;
  }
  
  .add-service button {
    background: #e9ecef;
    border: none;
    border-radius: 5px;
    padding: 0.5rem 1rem;
    cursor: pointer;
    color: #052C65;
    font-size: 1rem;
  }
  
  .add-service button:hover {
    background: #ced4da;
  }
  </style>
  