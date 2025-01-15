<template>
  <div class="licensing">
    <div class="globalHeader">
      <h1>Licensing</h1>
    </div>
    <div class="service-list">
      <div class="service-item" v-for="(service, index) in services" :key="index">
        <span>{{ service.name }}</span>
        <button class="edit-button" @click="openEditModal(index)">
          <img src="https://cdn-icons-png.flaticon.com/512/1827/1827933.png" alt="Edit" />
        </button>
      </div>
      <div class="add-service">
        <button @click="addNewService">+ Add New Service</button>
      </div>
    </div>
    <div v-if="blur" class="overlay" @click="closeModal"></div>
    <div v-if="showModal" class="modal-box">
      <div class="modalHeader">
        <span>Edit Service</span>
        <img :src="x" alt="Close" @click="closeModal" class="close-icon" />
      </div>
      <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
      <div class="modalBody">
        <label for="service-name">Name</label>
        <input id="service-name" type="text" v-model="editingService.name" class="modal-input" />
        <label for="service-description">Description</label>
        <textarea id="service-description" v-model="editingService.tooltip" class="modal-textarea"></textarea>
      </div>
      <div class="modalFooter">
        <button class="delete-button" @click="deleteService">Delete Service</button>
        <div class="action-buttons">
          <button class="cancel-button" @click="closeModal">Cancel</button>
          <button class="confirm-button" @click="saveChanges">Confirm</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import x from "@/assets/x-lg.svg";

export default {
  name: "licensing",
  data() {
    return {
      services: [
        { name: "Student-Driver's Permit", tooltip: "Apply for a student driver's permit." },
        { name: "New Driver's License (Non-Professional)", tooltip: "Apply for a new non-professional license." },
        { name: "Conductor's License", tooltip: "Apply for a conductor's license." },
      ],
      blur: false,
      showModal: false,
      editingIndex: null,
      editingService: {
        name: "",
        tooltip: "",
      },
      x
    };
  },
  methods: {
    addNewService() {
      this.services.push({ name: "New Service", tooltip: "New service description." });
    },
    openEditModal(index) {
      this.editingIndex = index;
      this.editingService = { ...this.services[index] };
      this.showModal = true;
      this.blur = true;
    },
    closeModal() {
      this.showModal = false;
      this.blur = false;
      this.editingService = { name: "", tooltip: "" };
    },
    saveChanges() {
      if (this.editingIndex !== null) {
        this.services[this.editingIndex] = { ...this.editingService };
      }
      this.closeModal();
    },
    deleteService() {
      if (this.editingIndex !== null) {
        this.services.splice(this.editingIndex, 1);
      }
      this.closeModal();
    },
  },
};
</script>

<style scoped>
.licensing {
  background-color: #e9ecef;
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
  border: 1px solid #dee2e6;
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
  color: #052c65;
  font-size: 1rem;
}

.add-service button:hover {
  background: #ced4da;
}

.overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: rgba(0, 0, 0, 0.5);
}

.modal-box {
  position: fixed;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  background: white;
  width: 400px;
  border-radius: 8px;
  box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.1);
  padding: 1.5rem;
  width: 38.9375rem;
}

.modalHeader {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1rem;
  font-weight: bold;
  font-size: 1.2rem;
}

.close-icon {
  width: 10px;
  height: 10px;
  cursor: pointer;
}

.modalBody {
  padding: 1rem;
}

.modalBody label {
  display: block;
  margin-bottom: 0.5rem;
  font-weight: bold;
}

.modal-input {
  width: 100%;
  padding: 0.5rem;
  border: 1px solid #ced4da;
  border-radius: 5px;
  margin-bottom: 1rem;
}

.modal-textarea {
  width: 100%;
  height: 100px;
  padding: 0.5rem;
  border: 1px solid #ced4da;
  border-radius: 5px;
  margin-bottom: 1rem;
}

.modalFooter {
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  gap: 1rem;
}

.delete-button {
  background: #FFFFFF;
  border: 1px solid #DC3545;
  color: #DC3545;
  border-radius: 5px;
  padding: 0.5rem 1rem;
  cursor: pointer;
  width: 100%;
  text-align: center;
}

.delete-button:hover {
  background: #ffcccc;
}

.action-buttons {
  display: flex;
  justify-content: flex-end;
  width: 100%;
  gap: 1rem;
}

.cancel-button {
  background: #e9ecef;
  border: 1px solid #ced4da;
  border-radius: 5px;
  padding: 0.5rem 1rem;
  cursor: pointer;
}

.confirm-button {
  background: #084298;
  color: white;
  border: none;
  border-radius: 5px;
  padding: 0.5rem 1rem;
  cursor: pointer;
}

.confirm-button:hover {
  background: #0056b3;
}
</style>
