<template>
  <div class="servicesOffered">
    <div class="globalHeader">
      <h1>Update Tickets</h1>
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
import { supabase } from "../../client/supabase";

export default {
  name: "servicesOffered",
  data() {
    return {
      ltoLogo,
      boxes: Array(3).fill(null),
      ServiceName: ["Driver's Licensing", "Vehicle Registration", "Law Enforcement"],
      ServiceDescription: ["This service covers the issuance of various types of driver’s licenses, from student permits to professional licenses. It also includes renewal, replacement, and assessments like written and practical driving exams.", 
      "This service involves the registration of new vehicles or renewal of existing registrations, ensuring compliance with national transportation laws. It includes the issuance of license plates, stickers, and official registration documents.", 
      "This service involves the encoding of alarm on driver's license and motor vehicles in relation to orders issued by competent courts or quasi-judicial bodies."],
    };
  },
  mounted() {
  },
  methods: {
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
  background: #052C65;
}

.line {
  width: 100%;
  height: 1.5px;
  background: #0a58ca;
}
</style>
