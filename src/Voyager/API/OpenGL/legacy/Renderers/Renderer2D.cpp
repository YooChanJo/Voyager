// #include "Renderer2D.h"
// #include "Core/Log.h"

// namespace Voyager {
        
//     OpenGLVertexBufferLayout VertexData::GetLayout() {
//         OpenGLVertexBufferLayout layout;
//         layout.Push<float>(3); // position
//         layout.Push<unsigned char>(4); // color
//         return layout;
//     }

//     Renderer2D::Renderer2D(/* OpenGLWindow& window */)/* : m_Window(&window) */ {
//         // m_TransformationStack.reserve(10); // reserve space for 10 matrices
//         m_TransformationStack.push_back(glm::mat4(1.0f)); // identity matrix
//         m_TransformationBack = &m_TransformationStack.back();
//     }

//     void Renderer2D::Push(const glm::mat4& matrix, bool override) {
//         if(override) {
//             m_TransformationStack.push_back(matrix);
//         } else {
//             m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
//         }
//         m_TransformationBack = &m_TransformationStack.back();
//     }

//     void Renderer2D::Pop() {
//         if (m_TransformationStack.size() > 1) {
//             m_TransformationStack.pop_back();
//             m_TransformationBack = &m_TransformationStack.back();
//         } else {
//             VG_CORE_ERROR("Cannot pop the last matrix from the stack!");
//         }
//     }
// }