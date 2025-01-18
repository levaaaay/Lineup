<template>
  <div class="letas">
    <div class="globalHeader">
      <h1>LETAS</h1>
    </div>
    <div class="container">
      <div class="boxHeader">
        <div class="boxHeaderTexts">
          <p>#</p>
          <p>Service</p>
          <p>Reference #</p>
          <p>Status</p>
        </div>
      </div>
      <div class="ticketBoxes">
        <div
          class="ticketBox"
          v-for="(item, index) in paginatedTickets"
          :key="index"
        >
          <p>{{ index + 1 + (currentPage - 1) * ticketsPerPage }}</p>
          <p>{{ item.service }}</p>
          <p>{{ item.reference }}</p>
          <div class="statusBox">
            <button
              class="statusButton"
              :class="getStatusClass(item.status)"
              @click.stop="toggleDropdown(index)"
            >
              {{ item.status }}
            </button>
            <div v-if="activeDropdown === index" class="dropdownMenu">
              <p
                v-for="status in ['Pending', 'Done', 'In Progress', 'Rejected']"
                :key="status"
                @click.stop="
                  updateStatus(
                    index + (currentPage - 1) * ticketsPerPage,
                    status
                  )
                "
                :class="getStatusClass(status)"
              >
                {{ status }}
              </p>
            </div>
          </div>
        </div>
      </div>

      <!-- Pagination Controls -->
      <div class="pagination">
        <button @click="changePage(-1)" :disabled="currentPage === 1">
          Previous
        </button>
        <span>Page {{ currentPage }} of {{ totalPages }}</span>
        <button @click="changePage(1)" :disabled="currentPage === totalPages">
          Next
        </button>
      </div>
    </div>
  </div>
</template>

<script>
  import { supabase } from "../client/supabase";

  export default {
    name: "letas",
    data() {
      return {
        ticketCount: [],
        activeDropdown: null,
        currentPage: 1,
        ticketsPerPage: 10, 
      };
    },
    computed: {
      paginatedTickets() {
        const start = (this.currentPage - 1) * this.ticketsPerPage;
        const end = start + this.ticketsPerPage;
        return this.ticketCount.slice(start, end);
      },
      totalPages() {
        return Math.ceil(this.ticketCount.length / this.ticketsPerPage);
      },
    },
    mounted() {
      this.getTickets();
    },
    methods: {
      toggleDropdown(index) {
        this.activeDropdown = this.activeDropdown === index ? null : index;
      },
      async updateStatus(index, newStatus) {
        const { data, error } = await supabase
          .from("tickets")
          .update({ status: newStatus })
          .eq("reference_number", this.ticketCount[index].reference);
        if (!error) {
          this.ticketCount[index].status = newStatus;
          this.activeDropdown = null;
        }
      },
      getStatusClass(status) {
        if (status === "Done") return "status-done";
        if (status === "In Progress") return "status-in-progress";
        if (status === "Pending") return "status-pending";
        return "status-rejected";
      },
      async getTickets() {
        const today = new Date(
          new Date().toLocaleString("en-US", { timeZone: "Asia/Manila" })
        );
        const currentDay = new Date(today);
        const dateString = currentDay.toLocaleDateString("en-CA");

        const { data, error } = await supabase
          .from("tickets")
          .select("transaction, reference_number, status, ticket_number")
          .eq("parent_service_id", 3)
          .gte("queue_date", `${dateString} 00:00:00`)
          .lte("queue_date", `${dateString} 23:59:59`);

        if (error) {
          console.error(error);
        }

        if (data) {
          const sortedData = data.sort(
            (a, b) => a.ticket_number - b.ticket_number
          );

          this.ticketCount = sortedData.map((item) => ({
            service: item.transaction,
            reference: item.reference_number,
            status: item.status,
          }));
        }
      },
      changePage(direction) {
        const newPage = this.currentPage + direction;
        if (newPage > 0 && newPage <= this.totalPages) {
          this.currentPage = newPage;
        }
      },
    },
  };
</script>

<style scoped>
  /* Add styles for pagination buttons */
  .pagination {
    display: flex;
    justify-content: center;
    align-items: center;
    margin-top: 1rem;
    gap: 1rem;
  }

  .pagination button {
    padding: 0.5rem 1rem;
    background-color: #052c65;
    color: white;
    border: none;
    border-radius: 5px;
    cursor: pointer;
  }

  .pagination button:disabled {
    background-color: #adb5bd;
    cursor: not-allowed;
  }
  .letas {
    background: #e9ecef;
  }

  .container {
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 3rem;
    gap: 0;
  }

  .boxHeader {
    width: 69rem;
    height: 3.0625rem;
    background: #052c65;
    display: flex;
  }

  .boxHeaderTexts {
    display: flex;
    justify-content: space-between;
    width: 100%;
  }

  .boxHeaderTexts p {
    color: white;
    font-weight: bold;
    margin: 0;
    flex: 1;
  }

  .boxHeaderTexts,
  .ticketBox {
    display: flex;
    align-items: center;
    width: 100%;
    padding: 0 1rem;
  }

  .boxHeaderTexts p,
  .ticketBox p {
    margin: 0;
    text-align: center;
    overflow: hidden;
    white-space: nowrap;
    text-overflow: ellipsis;
  }

  .boxHeaderTexts p:nth-child(1),
  .ticketBox p:nth-child(1) {
    flex: 1;
  }

  .boxHeaderTexts p:nth-child(2),
  .ticketBox p:nth-child(2) {
    flex: 3;
    text-align: left;
  }

  .boxHeaderTexts p:nth-child(3),
  .ticketBox p:nth-child(3) {
    flex: 2;
  }

  .boxHeaderTexts p:nth-child(4),
  .ticketBox .statusBox {
    flex: 2;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .ticketBox {
    width: 69rem;
    height: 3rem;
    background: #ffffff;
    border-bottom: 1px solid #dee2e6;
  }

  .statusBox {
    position: relative;
    overflow: visible;
    width: 13.125rem;
    height: 2rem;
    background-color: #ebe5fc;
    border-radius: 10px;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .statusButton {
    width: 100%;
    height: 100%;
    background: none;
    border: none;
    font-size: 1rem;
    cursor: pointer;
  }

  .dropdownMenu {
    position: absolute;
    top: 2.5rem;
    left: 0;
    background: white;
    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    border-radius: 5px;
    z-index: 10;
    width: 100%;
    display: flex;
    flex-direction: column;
    align-items: center;
  }

  .dropdownMenu p {
    margin: 0;
    padding: 0.5rem 1rem;
    cursor: pointer;
    text-align: center;
    display: block;
  }

  .dropdownMenu p:hover {
    background: #f0f0f0;
  }

  .dropdownMenu p {
    margin: 0;
    padding: 0.5rem 1rem;
    cursor: pointer;
    text-align: center;
    display: block;
  }

  .dropdownMenu p:hover {
    background: #f0f0f0;
  }

  .status-done {
    color: #198754;
  }

  .status-in-progress {
    color: #ffc107;
  }

  .status-pending {
    color: #adb5bd;
  }

  .status-rejected {
    color: #dc3545;
  }
</style>
