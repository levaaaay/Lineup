<template>
    <div class="servicesOffered">
      <div class="globalHeader">
        <h1>Services Offered</h1>
      </div>
      <div class="container">
        <div class="card">
          <div class="card-body">
            <h5 class="card-title">{{ ServiceName[0] }}</h5>
            <div class="line"></div>
            <p class="card-text">
              {{ ServiceDescription[0] }}
            </p>
          </div>
        </div>
        <div class="card">
          <div class="card-body">
            <h5 class="card-title">{{ ServiceName[1] }}</h5>
            <div class="line"></div>
            <p class="card-text">
              {{ ServiceDescription[1] }}
            </p>
          </div>
        </div>
        <div class="card">
          <div class="card-body">
            <h5 class="card-title">{{ ServiceName[2] }}</h5>
            <div class="line"></div>
            <p class="card-text">
              {{ ServiceDescription[2] }}
            </p>
          </div>
        </div>
      </div>
    </div>
  </template>
  
  <script>
  import ltoLogo from "@/assets/ltoLogo.svg";
  import { supabase } from "@/client/supabase";
  
  export default {
    name: "servicesOffered",
    data() {
      return {
        ltoLogo,
        boxes: Array(3).fill(null),
        ServiceName: [],
        ServiceDescription: [],
      };
    },
    mounted() {
      this.showServiceDetails();
    },
    methods: {
      async showServiceDetails() {
        const { data, error } = await supabase
          .from("services")
          .select("service_name, service_description")
          .eq("service_type", "main");
        if (error) {
          console.error(error);
        }
  
        this.ServiceName = data.map((service) => service.service_name);
        this.ServiceDescription = data.map(
          (service) => service.service_description
        );
      },
    },
  };
  </script>
  
  <style scoped>
  .servicesOffered {
    background: #dee2e6;
    height: 38rem;
  }
  
  h1 {
    font-weight: 800 !important;
    padding-top: 2.43rem;
    padding-bottom: 1rem;
  }
  
  h5,
  p {
    color: white;
  }
  
  .ltoLogo {
    width: 100px;
    height: 100px;
    margin-top: 23px;
  }
  
  .card {
    width: 21.875rem;
    height: 25.625rem;
    background: #084298;
  }
  
  .line {
    width: 100%;
    height: 1.5px;
    background: #0a58ca;
  }
  </style>
