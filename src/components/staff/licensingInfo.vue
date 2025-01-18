<template>
  <div class="licensing">
    <div class="globalHeader">
      <h1>Licensing</h1>
    </div>
    <div class="service-list">
      <div
        class="service-item"
        v-for="(service, index) in services"
        :key="index"
      >
        <span>{{ service.name }}</span>
        <button class="edit-button" @click="openEditModal(index)">
          <img
            src="https://cdn-icons-png.flaticon.com/512/1827/1827933.png"
            alt="Edit"
          />
        </button>
      </div>
      <div class="add-service">
        <button @click="addNewService">+ Add New Service</button>
      </div>
    </div>

    <!-- Overlay -->
    <div v-if="blur" class="overlay" @click="closeAllModals"></div>

    <!-- Edit Modal -->
    <div v-if="showModal" class="modal-box">
      <div class="modalHeader">
        <span>Edit Service</span>
        <img :src="x" alt="Close" @click="closeModal" class="close-icon" />
      </div>
      <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
      <div class="modalBody">
        <label for="service-name">Name</label>
        <input
          id="service-name"
          type="text"
          v-model="editingService.name"
          class="modal-input"
        />
        <label for="service-description">Description</label>
        <textarea
          id="service-description"
          v-model="editingService.tooltip"
          class="modal-textarea"
        ></textarea>
        <label for="transaction-time">Transaction Time</label>
        <input
          id="transaction-time"
          type="text"
          v-model="editingService.time"
          class="modal-input"
          placeholder="Transaction Time(In Minutes)"
        />
      </div>
      <div class="modalFooter">
        <button class="delete-button" @click="deleteService">
          Delete Service
        </button>
        <div class="action-buttons">
          <button class="cancel-button" @click="closeModal">Cancel</button>
          <button class="confirm-button" @click="saveChanges">Confirm</button>
        </div>
      </div>
    </div>

    <!-- Add New Service Modal -->
    <div v-if="showAddModal" class="modal-box">
      <div class="modalHeader">
        <span>Add New Service</span>
        <img :src="x" alt="Close" @click="closeAddModal" class="close-icon" />
      </div>
      <div style="height: 1px; width: 100%; background-color: #ced4da"></div>
      <div class="modalBody">
        <label for="new-service-name">Name</label>
        <input
          id="new-service-name"
          type="text"
          v-model="newService.name"
          class="modal-input"
          placeholder="Service Name"
        />
        <label for="new-service-description">Description</label>
        <textarea
          id="new-service-description"
          v-model="newService.tooltip"
          class="modal-textarea"
          placeholder="Description"
        ></textarea>
        <label for="new-transaction-time">Transaction Time</label>
        <input
          id="new-transaction-time"
          type="text"
          v-model="newService.time"
          class="modal-input"
          placeholder="Transaction Time(In Minutes)"
        />
      </div>
      <div class="modalFooter">
        <div class="action-buttons">
          <button class="cancel-button" @click="closeAddModal">Cancel</button>
          <button class="confirm-button" @click="addServiceToDatabase">
            Confirm
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import { supabase } from "@/client/supabase";
  import x from "@/assets/x-lg.svg";

  export default {
    name: "letas",
    data() {
      return {
        services: [],
        blur: false,
        showModal: false,
        showAddModal: false,
        editingIndex: null,
        editingService: {
          name: "",
          tooltip: "",
          time: null,
        },
        newService: {
          name: "",
          tooltip: "",
          time: null,
        },
        x,
      };
    },
    mounted() {
      this.showService();
    },
    methods: {
      async showService() {
        const { data, error } = await supabase
          .from("services")
          .select("service_name, service_description, transaction_time")
          .eq("parent_service_id", 1);

        this.services = data.map((service) => ({
          name: service.service_name,
          tooltip: service.service_description,
          time: service.transaction_time,
        }));
      },
      addNewService() {
        this.showAddModal = true;
        this.blur = true;
      },
      closeAddModal() {
        if (this.services[this.services.length - 1] === this.newService) {
          this.services.pop();
        }
        this.showAddModal = false;
        this.blur = false;
      },
      async addServiceToDatabase() {
        if (isNaN(this.newService.time)) {
            alert("Please enter a valid number for transaction time.");
            return;
          }
        else{
          console.log(this.newService.time)
        }
        try {
          const { data, error } = await supabase.from("services").insert([
            {
              service_name: this.newService.name,
              service_description: this.newService.tooltip,
              transaction_time: this.newService.time,
              parent_service_id: 1,
            },
          ]);

          if (error) {
            console.error("Error adding service:", error);
          } else {
            console.log("Service added successfully!", data);
          }
        } catch (err) {
          console.error("Unexpected error:", err);
        } finally {
          this.closeAddModal();
          this.services.push(this.newService);
          this.newService = { name: "", tooltip: "", time: null };
        }
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
        this.editingService = { name: "", tooltip: "", time: null };
      },
      async saveChanges() {
        if (this.editingIndex !== null) {
          const updatedService = { ...this.editingService };
          
          if (isNaN(updatedService.time)) {
            alert("Please enter a valid number for transaction time.");
            return;
          }
          try {
            const { error } = await supabase
              .from("services")
              .update({
                service_name: updatedService.name,
                service_description: updatedService.tooltip,
                transaction_time: updatedService.time, 
              })
              .eq("service_name", this.services[this.editingIndex].name);

            if (error) {
              console.error("Error updating service:", error.message);
            } else {
              this.services[this.editingIndex] = updatedService;
            }
          } catch (err) {
            console.error("Unexpected error updating service:", err);
          } finally {
            this.closeModal();
          }
        }
      },
      async deleteService() {
        if (this.editingIndex !== null) {
          const serviceToDelete = this.services[this.editingIndex];

          try {
            const { error } = await supabase
              .from("services")
              .delete()
              .eq("service_name", serviceToDelete.name);

            if (error) {
              console.error("Error deleting service:", error);
              return;
            }

            this.services.splice(this.editingIndex, 1);
          } catch (err) {
            console.error("Unexpected error deleting service:", err);
          } finally {
            this.closeModal();
          }
        }
      },
      closeAllModals() {
        this.closeModal();
        this.closeAddModal();
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
    background: #ffffff;
    border: 1px solid #dc3545;
    color: #dc3545;
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
